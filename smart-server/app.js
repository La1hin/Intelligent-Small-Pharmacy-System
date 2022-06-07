const express = require('express')
const cors = require('cors')    //跨域处理
const router = require('./router')  //路由
const user = require('./user')  //用户名和密码
const Users = require('./models/Users')  //mongoose数据库
const jwt = require('jsonwebtoken');  //token
const path = require('path');
const proxyMiddleWare = require('http-proxy-middleware');//引入反向代理的插件
const net = require('net');//TCP服务器
const expressWS = require('express-ws')  //websocket服务引入
const https=require('https')
const fs=require('fs')
const app = express()
expressWS(app) //载入websocket


app.use(express.static(__dirname + "/public/dist"));//__dirname 当前目录
const { createProxyMiddleware } = require('http-proxy-middleware');//引入插件
//反向代理配置
app.use(createProxyMiddleware("/api", {
    target: "https://106.52.146.151:3333",//目标后端服务地址
    changeOrigoin: true,//是否跨域
    pathRewrite: { '^/api': '' }//重写
}));
//cors跨域配置
var corsOptions = {
    origin: '*',
    optionsSuccessStatus: 204, // 对于旧版浏览器的支持
    // methods: 'GET,POST'
}
//挂载cors
app.use(cors(corsOptions))

//拦截token验证
app.use((req, res, next) => {
    const token = req.get('token')
    if (req.path != "/bgstyle" && req.path != "/userslogin" && req.path != "/usersregister" && req.path != "/wxgethome") {
        return tokenVerify(token, next, res)
    }
    next()
})
//挂载路由
app.use(router)

// //websocket服务
// app.ws('/', function (ws, req) {
//     console.log('connect success')
//     console.log(ws._protocol);
//     // 使用 ws 的 send 方法向连接另一端的客户端发送数据
//     ws.send('connect to express server with WebSocket success')
//     //清除actionlattice
//     //判断是否存在取药任务
//     // Users.watch('change', (val) => {
//     //     console.log(val);
//     // })
//     ws.on('message', function (msg) {
//         // 判断msg是否为true,完成取药，加入取药记录
//         console.log(msg);
//     })

//     ws.on('close', function (e) {

//         console.log('close connection')
//     })
// })
//TCP服务器
const TCPserver = net.createServer(function (socket) {

    activeDelete()
    //断开连接清除数据库中actionlattice的内容
    //判断actionlattice是否为空，如果有数据就给广和通发数据
    //接收到1，说明完成取药动作
    let total = 0, sendFlag = 0, orders = 0;
    //定时器查看actionlattice是否为空

    setInterval(function () {
        Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            //如果完成一个订单，则删除一个订单任务,并加到完成订单内
            if (orders) {
                orders = 0
                socket.write("Received")

                return Users.find(user, (err, ret) => {
                    if (err) {
                        return console.log(err)
                    }
                    var oldArr = ret[0].actionlattice
                    var oldRecord = ret[0].record

                    var newRecordObj = {}
                    var date = new Date()
                    newRecordObj.date = `${date.getFullYear()}-${date.getMonth() + 1}-${date.getDate()} ${date.toTimeString().substring(0, 8)}`;
                    newRecordObj.record = oldArr[0].checkedArr

                    oldRecord.unshift(newRecordObj)
                    oldArr.shift()
                    Users.findOneAndUpdate(user, { record: oldRecord }, { new: true }, (err, ret) => {
                        if (err) {
                            return console.log(err)
                        }
                        //ret返回更新后的数据
                        return ret
                    })
                    return Users.findOneAndUpdate(user, { actionlattice: oldArr }, { new: true }, (err, ret) => {
                        if (err) {
                            return console.log(err)
                        }
                        //ret返回更新后的数据
                        return ret
                    })

                })
            }
            //如果存在要取的药物
            else if (ret[0].actionlattice.length) {
                let arr = ret[0].actionlattice[0].checkedArr
                let Arrlength = arr.length
                if (sendFlag) {
                    if (total == Arrlength) {
                        sendFlag = 0
                        total = 0
                        orders = 1
                        return
                    }
                    let totalObj=JSON.parse(arr[total]) 
                    let obj={x:totalObj.x,y:totalObj.y}
                    socket.write(JSON.stringify(obj))
                    total++
                    sendFlag = 0
                }
            }
        })
    }, 1000);

    //1  完成
    //监听data事件
    socket.on("data", function (data) {
        console.log(data)
        if (data.toString() == '1') {
            sendFlag = 1
        }
    });
    //socket.destroy()断开TCP连接
    socket.on("close", function () {
         activeDelete();
         return
    });
    socket.on("error", function () {
         activeDelete();
         return;
    });
});

//删除actionlattice数据
function activeDelete () {
    console.log("del");
    return Users.find(user, (err, ret) => {
        if (err) {
            return console.log(err)
        }
        var newArr = []
        return Users.findOneAndUpdate(user, { actionlattice: newArr }, { new: true }, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            //ret返回更新后的数据
            return ret
        })
    })
}
//查看数据库是否为空
async function activeFind () {
    let arr = await Users.find(user, (err, ret) => {
        if (err) {
            return console.log(err)
        }
        return ret
    })
    return arr
}

//TCP端口监听
TCPserver.listen(3500, function (e) {
    console.log("TCP服务正在监听中。。。")
});

//设置监听端口
// app.listen(3333, (err) => {
//     if (err) {
//         return err;
//     }
//     console.log('running....');
// })
https
  .createServer(
    {
      key: fs.readFileSync("smart.chendx.info.key"),
      cert: fs.readFileSync("smart.chendx.info_bundle.crt"),
    },
    app
  )
  .listen(3333);

//token验证
function tokenVerify (token, next, res) {
    //密匙
    const signKey = '$1$CLlgVqUg$A.h37SfpUbmzRTIi3DxXH1'
    jwt.verify(token, signKey, (err, decode) => {
        if (err) {
            return res.sendStatus(401)
        }
        user.username = decode.username
        user.password = decode.password
        next()
    })
    return
}
