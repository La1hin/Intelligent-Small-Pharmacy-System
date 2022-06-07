const axios = require('axios')
const express = require('express')
const Users = require('./models/Users')
const jwt = require('jsonwebtoken');
const user = require('./user')
const router = express.Router()

var cheerio = require('cheerio');//操作dom的库


router.get('/bgstyle', (req, res, next) => {
    const token = req.get('token')
    //自动登录跳过登录页
    if (token && token != "null") {
        //密匙
        const signKey = '$1$CLlgVqUg$A.h37SfpUbmzRTIi3DxXH1'
        return jwt.verify(token, signKey, (err, decode) => {
            if (err) {
                return getbackground(res)
            } else {
                return res.sendStatus(209)
            }
        })
    }
    getbackground(res)
    async function getbackground (res) {
        const { data: result } = await axios({
            url: 'https://cn.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&nc=1586183781119&pid=hp&uhd=1&uhdwidth=1920&uhdheight=1080',
            method: 'get'
        })
        let { url } = result.images[0]
        // 通过正则，将图片链接改为超高清版
        //let link = url.match(/.*?(?=&)/)
        let img = `https://cn.bing.com${url}`
        return res.send(img)
    }
})
    //处理注册请求,注册成功返回1
    .get('/usersregister', (req, res, next) => {
        //user为object类型
        const user = req.query
        Users.find({ username: user.username }, (err, ret) => {
            if (err) {
                return err;
            }
            if (ret.length == 0) {
                return new Users(user).save((err, ret) => {
                    if (err) {
                        return console.log(err)
                    }
                    return res.status(200).json({
                        code: 1
                    })
                })
            }
            return res.status(200).json({
                code: 0
            })
        })
    })
    //处理登录请求,登录成功返回1
    .get('/userslogin', (req, res, next) => {
        //user为object类型
        const user = req.query
        Users.find(user, (err, ret) => {
            if (err) {
                return err;
            }
            if (ret.length == 0) {
                return res.status(200).json({
                    code: 0
                })
            }
            let setToken = jwt.sign(user, '$1$CLlgVqUg$A.h37SfpUbmzRTIi3DxXH1', {
                expiresIn: 60 * 60 * 1 * 24 // 1天过期
            });
            return res.status(200).json({
                code: 1,
                token: setToken
            })
        })
    })
    //处理home页面数据
    .get('/homedata', (req, res, next) => {
        Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            //ret[0]拿到user对象数据
            return res.send(ret[0]);
        })
    })
    //设置药柜信息
    .get('/setcabinet', (req, res, next) => {
        const query = req.query
        let objflag = true
        //判断药柜参数是否有空
        for (let k in query) {
            if (!query[k]) {
                objflag = false
            }
        }
        //如果没有空就生成药柜数据
        if (objflag) {
            let updataobj = [];
            Users.find(user, (err, ret) => {
                if (err) {
                    return console.log(err)
                }
                //id为最大的id+1
                let count = 0;
                ret[0].cabinet.forEach(item => {
                    if (item.id > count) { count = item.id }
                });
                query.id = count + 1
                //生成药柜格子的二维数组
                const newLatticeArr = Array.from(Array(parseInt(query.latticeY)), () => new Array(parseInt(query.latticeX)));
                query.latticeArr = newLatticeArr
                updataobj[0] = query
                //合并数组
                updataobj = [...ret[0].cabinet, ...updataobj]
                //更新数据库
                return Users.findOneAndUpdate(user, { cabinet: updataobj }, { new: true }, (err, ret) => {
                    if (err) {
                        return console.log(err)
                    }
                    //ret返回更新后的数据
                    return res.send(ret)
                })
            })

        }
    })
    //删除药柜
    .get('/removecabniet', (req, res, next) => {
        const id = req.query.id
        Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            let updataobj = ret[0].cabinet
            //遍历数据库查找id相同的
            updataobj.forEach((item, index) => {
                if (item.id == id) {
                    //删除这条数据
                    updataobj.splice(index, 1)
                }
            });
            //将删除后的数据更新到数据库
            return Users.findOneAndUpdate(user, { cabinet: updataobj }, { new: true }, (err, ret) => {
                if (err) {
                    return console.log(err)
                }
                //ret返回更新后的数据
                return res.send(ret)
            })
        })
    })
    //添加格子药品
    .get('/addlattice', (req, res, next) => {
        const query = req.query, id = req.query.id
        Users.find(user, async (err, ret) => {
            if (err) {
                return console.log(err)
            }
            let updataobj = ret[0].cabinet
            const { data: result } = await axios({
                url: `http://xiaobai.klizi.cn/API/img/baidu.php?msg=${encodeURIComponent(query.value)}&page=1`,
                method: 'get'
            })
            //遍历数据库查找id相同的
            updataobj.forEach((item, index) => {
                if (item.id == id) {
                    //删除这条数据
                    // updataobj.splice(index, 1)
                    let obj = {
                        value: query.value,
                        imgUrl: result.data[0].hoverUrl
                    }
                    updataobj[index].latticeArr[query.y][query.x] = obj
                }
            });
            // 将删除后的数据更新到数据库
            return Users.findOneAndUpdate(user, { cabinet: updataobj }, { new: true }, (err, ret) => {
                if (err) {
                    return console.log(err)
                }
                //ret返回更新后的数据
                return res.send(ret)
            })
        })
    })
    //删除格子药品
    .get('/deletelattice', (req, res, next) => {
        const query = req.query, id = req.query.id
        Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            let updataobj = ret[0].cabinet
            //遍历数据库查找id相同的
            updataobj.forEach((item, index) => {
                if (item.id == id) {
                    //删除这条数据
                    updataobj[index].latticeArr[query.y][query.x] = ''
                }
            });
            // 将删除后的数据更新到数据库
            return Users.findOneAndUpdate(user, { cabinet: updataobj }, { new: true }, (err, ret) => {
                if (err) {
                    return console.log(err)
                }
                //ret返回更新后的数据
                return res.send(ret)
            })
        })
    })
    //获取要取的药品
    .get('/getActionLattice', (req, res, next) => {
        console.log(req.query, typeof (req.query));
        // var queryArr = req.query.checkedArr, updataobj = [], newArr = [];
        // queryArr.forEach(item => newArr.push(JSON.parse(item)));
        return Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            updataobj = ret[0].actionlattice
            updataobj.push(req.query)
            return Users.findOneAndUpdate(user, { actionlattice: updataobj }, { new: true }, (err, ret) => {
                if (err) {
                    return console.log(err)
                }
                //ret返回更新后的数据
                return res.send(ret)
            })
        })

    })
    //获取药柜取药记录
    .get('/getrecord', (req, res, next) => {
        return Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            res.send(ret[0].record)
        })
    })
//处理home页面数据
    .get('/wxgethome', (req, res, next) => {
        Users.find(user, (err, ret) => {
            if (err) {
                return console.log(err)
            }
            //ret[0]拿到user对象数据
            return res.send(ret[0]);
        })
    })
module.exports = router