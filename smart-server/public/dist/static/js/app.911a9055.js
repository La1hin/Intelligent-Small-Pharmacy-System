(function(e){function t(t){for(var n,o,s=t[0],c=t[1],u=t[2],p=0,d=[];p<s.length;p++)o=s[p],Object.prototype.hasOwnProperty.call(a,o)&&a[o]&&d.push(a[o][0]),a[o]=0;for(n in c)Object.prototype.hasOwnProperty.call(c,n)&&(e[n]=c[n]);l&&l(t);while(d.length)d.shift()();return i.push.apply(i,u||[]),r()}function r(){for(var e,t=0;t<i.length;t++){for(var r=i[t],n=!0,s=1;s<r.length;s++){var c=r[s];0!==a[c]&&(n=!1)}n&&(i.splice(t--,1),e=o(o.s=r[0]))}return e}var n={},a={app:0},i=[];function o(t){if(n[t])return n[t].exports;var r=n[t]={i:t,l:!1,exports:{}};return e[t].call(r.exports,r,r.exports,o),r.l=!0,r.exports}o.m=e,o.c=n,o.d=function(e,t,r){o.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:r})},o.r=function(e){"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},o.t=function(e,t){if(1&t&&(e=o(e)),8&t)return e;if(4&t&&"object"===typeof e&&e&&e.__esModule)return e;var r=Object.create(null);if(o.r(r),Object.defineProperty(r,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var n in e)o.d(r,n,function(t){return e[t]}.bind(null,n));return r},o.n=function(e){var t=e&&e.__esModule?function(){return e["default"]}:function(){return e};return o.d(t,"a",t),t},o.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},o.p="";var s=window["webpackJsonp"]=window["webpackJsonp"]||[],c=s.push.bind(s);s.push=t,s=s.slice();for(var u=0;u<s.length;u++)t(s[u]);var l=c;i.push([0,"chunk-vendors"]),r()})({0:function(e,t,r){e.exports=r("56d7")},"0403":function(e,t,r){"use strict";r("26ce")},"10d6":function(e,t,r){},2115:function(e,t,r){"use strict";r("10d6")},2395:function(e,t,r){},"266b":function(e,t,r){},"26ce":function(e,t,r){},"2d2b":function(e,t,r){"use strict";r("266b")},4994:function(e,t,r){},"56d7":function(e,t,r){"use strict";r.r(t);var n={};r.r(n),r.d(n,"getBingBackground",(function(){return te})),r.d(n,"getUsersLogin",(function(){return re})),r.d(n,"getUsersRegister",(function(){return ne})),r.d(n,"getUsersHome",(function(){return ae}));r("0fb7"),r("450d");var a=r("f529"),i=r.n(a),o=(r("9e1f"),r("6ed5")),s=r.n(o),c=(r("560b"),r("dcdc")),u=r.n(c),l=(r("1951"),r("eedf")),p=r.n(l),d=(r("e260"),r("e6cf"),r("cca6"),r("a79d"),r("b0c0"),r("2b0e")),m=function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("div",{attrs:{id:"app"}},[r("router-view")],1)},f=[],v=(r("7c55"),r("2877")),g={},h=Object(v["a"])(g,m,f,!1,null,null,null),b=h.exports,w=r("8c4f"),x=function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("div",{ref:"bgStyle",staticClass:"container"},[r("router-view",{staticClass:"lORr"})],1)},y=[],_=r("1da1"),k=(r("96cf"),{data:function(){return{}},created:function(){this.getback()},methods:{getback:function(){var e=this;return Object(_["a"])(regeneratorRuntime.mark((function t(){var r;return regeneratorRuntime.wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.next=2,e.$store.dispatch("reqBing");case 2:r=t.sent,e.$refs.bgStyle.style.backgroundImage="url(".concat(r,")");case 4:case"end":return t.stop()}}),t)})))()}}}),$=k,j=(r("2d2b"),Object(v["a"])($,x,y,!1,null,"6fb3f231",null)),O=j.exports,P=function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("div",{staticClass:"loginContainer"},[r("table",[e._m(0),r("tbody",{on:{keyup:function(t){return!t.type.indexOf("key")&&e._k(t.keyCode,"enter",13,t.key,"Enter")?null:e.toHome.apply(null,arguments)}}},[r("div",[r("input",{directives:[{name:"model",rawName:"v-model",value:e.username,expression:"username"}],attrs:{type:"text",placeholder:"请输入用户名或账户"},domProps:{value:e.username},on:{input:function(t){t.target.composing||(e.username=t.target.value)}}})]),r("div",[r("input",{directives:[{name:"model",rawName:"v-model",value:e.password,expression:"password"}],attrs:{type:"password",placeholder:"请输入密码"},domProps:{value:e.password},on:{input:function(t){t.target.composing||(e.password=t.target.value)}}})]),r("div",{staticClass:"autologin"},[r("el-checkbox",{attrs:{label:"自动登录","text-color":"#fff"},model:{value:e.checked,callback:function(t){e.checked=t},expression:"checked"}}),r("p",[e._v("没有账户?"),r("a",{on:{click:e.toRegister}},[e._v("注册")]),e._v("一个吧")])],1),r("button",{staticClass:"loginBtn",on:{click:e.toHome}},[e._v("登录")])])])])},R=[function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("thead",[r("h3",[e._v("Login")])])}],S={data:function(){return{checked:!0,username:"",password:""}},methods:{toRegister:function(){this.$router.push("/register")},toHome:function(){var e=this;return Object(_["a"])(regeneratorRuntime.mark((function t(){var r,n,a,i,o;return regeneratorRuntime.wrap((function(t){while(1)switch(t.prev=t.next){case 0:if(r=e.username,n=e.password,a=e.checked,!r||!n){t.next=9;break}return i={username:r,password:n},t.next=5,e.$store.dispatch("reqLogin",i);case 5:o=t.sent,o.code?(a&&localStorage.setItem("smartToken",o.token),e.$message({message:"登录成功",type:"success"})):e.$message.error("用户名或密码错误"),t.next=10;break;case 9:e.$message({message:"请输入用户名和密码",type:"warning"});case 10:case"end":return t.stop()}}),t)})))()}},computed:{}},C=S,H=(r("0403"),Object(v["a"])(C,P,R,!1,null,"b90ef672",null)),N=H.exports,E=function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("div",{staticClass:"loginContainer"},[r("table",[e._m(0),r("tbody",[r("div",[r("input",{directives:[{name:"model",rawName:"v-model",value:e.username,expression:"username"}],attrs:{type:"text",placeholder:"请输入用户名或账户"},domProps:{value:e.username},on:{input:function(t){t.target.composing||(e.username=t.target.value)}}})]),r("div",[r("input",{directives:[{name:"model",rawName:"v-model",value:e.password,expression:"password"}],attrs:{type:"password",placeholder:"请输入密码"},domProps:{value:e.password},on:{input:function(t){t.target.composing||(e.password=t.target.value)}}})]),r("button",{on:{click:e.toLogin}},[e._v("注册")])])])])},W=[function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("thead",[r("h3",[e._v("Register")])])}],q={data:function(){return{username:"",password:""}},methods:{toLogin:function(){var e=this;return Object(_["a"])(regeneratorRuntime.mark((function t(){var r,n,a,i;return regeneratorRuntime.wrap((function(t){while(1)switch(t.prev=t.next){case 0:if(r=e.username,n=e.password,!r||!n){t.next=9;break}return a={username:r,password:n},t.next=5,e.$store.dispatch("reqRegister",a);case 5:i=t.sent,i?(e.$message({message:"注册成功",type:"success"}),e.$router.push("/login")):e.$message.error("用户名已存在"),t.next=10;break;case 9:e.$message({message:"请输入用户名和密码",type:"warning"});case 10:case"end":return t.stop()}}),t)})))()}}},B=q,I=(r("2115"),Object(v["a"])(B,E,W,!1,null,"103c91de",null)),L=I.exports,T=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{staticClass:"homeContainer"},[e._m(0),n("div",{staticClass:"body"},[n("div",{staticClass:"cabinetItem"}),n("div",{staticClass:"cabinet"},[n("div",{staticClass:"pharmacy"},[n("img",{attrs:{src:r("d1da"),alt:""},on:{click:e.toSetting}})]),n("el-button",{attrs:{type:"primary"},on:{click:e.getHomeData}},[e._v("一键取药")])],1)]),n("table",{directives:[{name:"show",rawName:"v-show",value:e.isShow,expression:"isShow"}],staticClass:"setting"},[e._m(1),n("tbody",[n("div",[n("label",{attrs:{for:"input1"}},[e._v("柜子名: ")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.cabinetName,expression:"cabinetName"}],attrs:{type:"text",id:"input1"},domProps:{value:e.cabinetName},on:{input:function(t){t.target.composing||(e.cabinetName=t.target.value)}}})]),n("div",[n("label",{attrs:{for:"input2"}},[e._v("柜子宽: ")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.cabinetWidth,expression:"cabinetWidth"}],attrs:{type:"text",id:"input2"},domProps:{value:e.cabinetWidth},on:{input:function(t){t.target.composing||(e.cabinetWidth=t.target.value)}}})]),n("div",[n("label",{attrs:{for:"input3"}},[e._v("柜子高: ")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.cabinetHeight,expression:"cabinetHeight"}],attrs:{type:"text",id:"input3"},domProps:{value:e.cabinetHeight},on:{input:function(t){t.target.composing||(e.cabinetHeight=t.target.value)}}})]),n("div",[n("label",{attrs:{for:"input4"}},[e._v("格子数(x):")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.latticeX,expression:"latticeX"}],attrs:{type:"text",id:"input4"},domProps:{value:e.latticeX},on:{input:function(t){t.target.composing||(e.latticeX=t.target.value)}}})]),n("div",[n("label",{attrs:{for:"input5"}},[e._v("格子数(y):")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.latticeY,expression:"latticeY"}],attrs:{type:"text",id:"input5"},domProps:{value:e.latticeY},on:{input:function(t){t.target.composing||(e.latticeY=t.target.value)}}})]),n("div",[n("label",{attrs:{for:"input6"}},[e._v("格子宽: ")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.latticeWidth,expression:"latticeWidth"}],attrs:{type:"text",id:"input6"},domProps:{value:e.latticeWidth},on:{input:function(t){t.target.composing||(e.latticeWidth=t.target.value)}}})]),n("div",[n("label",{attrs:{for:"input7"}},[e._v("格子高: ")]),n("input",{directives:[{name:"model",rawName:"v-model",value:e.latticeHeight,expression:"latticeHeight"}],attrs:{type:"text",id:"input7"},domProps:{value:e.latticeHeight},on:{input:function(t){t.target.composing||(e.latticeHeight=t.target.value)}}})]),n("div",[n("button",{staticClass:"cancelBtn btn",on:{click:e.cancel}},[e._v("取消")]),n("button",{staticClass:"confirmBtn btn",on:{click:e.confirm}},[e._v("确认")])])])]),n("div",{directives:[{name:"show",rawName:"v-show",value:e.isShow,expression:"isShow"}],staticClass:"bg"})])},X=[function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("div",{staticClass:"header"},[r("h1",[e._v("大浪,该吃药啦")]),r("div",[r("a",[e._v("用户名")]),r("a",[e._v("取药记录")])])])},function(){var e=this,t=e.$createElement,r=e._self._c||t;return r("thead",[r("h3",[e._v("设置药柜信息")])])}],Y={data:function(){return{isShow:!1,cabinetName:"",cabinetWidth:"",cabinetHeight:"",latticeX:"",latticeY:"",latticeWidth:"",latticeHeight:"",arr:[]}},methods:{toSetting:function(){this.isShow=!0},cancel:function(){this.isShow=!1},confirm:function(){this.cabinetName,this.cabinetWidth,this.cabinetHeight,this.latticeX,this.latticeY,this.latticeWidth,this.latticeHeight;this.isShow=!1},getHomeData:function(){var e=this;return Object(_["a"])(regeneratorRuntime.mark((function t(){var r;return regeneratorRuntime.wrap((function(t){while(1)switch(t.prev=t.next){case 0:return t.prev=0,t.next=3,e.$store.dispatch("reqHome");case 3:r=t.sent,console.log(r),t.next=11;break;case 7:t.prev=7,t.t0=t["catch"](0),e.$message.error("请重新登录"),e.$router.push("/login");case 11:case"end":return t.stop()}}),t,null,[[0,7]])})))()}}},M=Y,U=(r("eb93"),Object(v["a"])(M,T,X,!1,null,"7b391fa1",null)),D=U.exports,J=[{path:"/",component:O,children:[{path:"login",component:N},{path:"register",component:L},{path:"/",redirect:"/login"}]},{path:"/home",component:D}];d["default"].use(w["a"]);var A=new w["a"]({mode:"hash",routes:J});A.beforeEach((function(e,t,r){var n=localStorage.getItem("smartToken");"/login"==e.path||"/register"==e.path||n||r("/login"),r()}));var z=A,F=(r("d3b7"),r("d9e2"),r("2f62")),G=r("bc3a"),K=r.n(G),Q=r("323e"),V=r.n(Q),Z=(r("a5d8"),K.a.create({baseURL:"/api",timeout:1e4}));Z.interceptors.request.use((function(e){return localStorage.getItem("smartToken")&&(e.headers.token=localStorage.getItem("smartToken")),V.a.start(),e})),Z.interceptors.response.use((function(e){return V.a.done(),e.data}),(function(e){return Promise.reject(new Error("faile"))}));var ee=Z,te=function(){return ee({url:"/bgstyle",method:"get"})},re=function(e){return ee({url:"/userslogin",method:"get",params:e})},ne=function(e){return ee({url:"/usersregister",method:"get",params:e})},ae=function(){return ee({url:"/homedata",method:"get"})};d["default"].use(F["a"]);var ie=new F["a"].Store({state:{},mutations:{},actions:{reqBing:function(e){return Object(_["a"])(regeneratorRuntime.mark((function t(){var r;return regeneratorRuntime.wrap((function(t){while(1)switch(t.prev=t.next){case 0:return e.commit,t.next=3,te();case 3:if(r=t.sent,!r){t.next=8;break}return t.abrupt("return",r);case 8:return t.abrupt("return",Promise.reject(new Error("faile")));case 9:case"end":return t.stop()}}),t)})))()},reqLogin:function(e,t){return Object(_["a"])(regeneratorRuntime.mark((function r(){var n;return regeneratorRuntime.wrap((function(r){while(1)switch(r.prev=r.next){case 0:return e.commit,r.next=3,re(t);case 3:if(n=r.sent,!n){r.next=8;break}return r.abrupt("return",n);case 8:return r.abrupt("return",Promise.reject(new Error("faile")));case 9:case"end":return r.stop()}}),r)})))()},reqRegister:function(e,t){return Object(_["a"])(regeneratorRuntime.mark((function r(){var n;return regeneratorRuntime.wrap((function(r){while(1)switch(r.prev=r.next){case 0:return e.commit,r.next=3,ne(t);case 3:if(n=r.sent,!n){r.next=8;break}return r.abrupt("return",n.code);case 8:return r.abrupt("return",Promise.reject(new Error("faile")));case 9:case"end":return r.stop()}}),r)})))()},reqHome:function(){return Object(_["a"])(regeneratorRuntime.mark((function e(){var t;return regeneratorRuntime.wrap((function(e){while(1)switch(e.prev=e.next){case 0:return e.prev=0,e.next=3,ae();case 3:return t=e.sent,e.abrupt("return",t);case 7:return e.prev=7,e.t0=e["catch"](0),e.abrupt("return",Promise.reject(new Error("faile")));case 10:case"end":return e.stop()}}),e,null,[[0,7]])})))()}},modules:{}});r("0fae");d["default"].config.productionTip=!1,d["default"].component(p.a.name,p.a),d["default"].component(u.a.name,u.a),new d["default"]({router:z,store:ie,beforeCreate:function(){d["default"].prototype.$bus=this,d["default"].prototype.$API=n,d["default"].prototype.$msgbox=s.a,d["default"].prototype.$alert=s.a.alert,d["default"].prototype.$message=i.a},render:function(e){return e(b)}}).$mount("#app")},"7c55":function(e,t,r){"use strict";r("2395")},d1da:function(e,t,r){e.exports=r.p+"static/img/add.b4548431.png"},eb93:function(e,t,r){"use strict";r("4994")}});
//# sourceMappingURL=app.911a9055.js.map