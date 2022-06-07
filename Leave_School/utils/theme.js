import { Http } from './http';

class Theme {
    static async getHome() {
        const res = await Http.request({
            url: `http://smart.chendx.info:3333/`,
            data: {
            }
        })
        return res.data
    }

}

export {
    Theme
}

