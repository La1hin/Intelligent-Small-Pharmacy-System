import { promisic } from './util'

class Http {
    static async request({url, data,  method = 'GET'}){
        return await promisic(wx.request)({
            url: `${url}`,
            data,
            method,
        })
    }
}
class PostHttp {
    static async request({url, data,  method = 'POST'}){
        return await promisic(wx.request)({
            url: `${url}`,
            data,
            method,
        })
    }
}
export {
  Http,
  PostHttp
}

