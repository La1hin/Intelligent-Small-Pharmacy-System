
import { Theme } from "../../utils/theme";
Page({

    /**
     * 页面的初始数据
     */
    data: {
        cabinet: [],
        show: true
    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function (options) {

    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady: function () {
        let that = this
        function req(){
            wx.request({
                url: 'https://smart.chendx.info:3333/wxgethome',
                data: {
                },
                header: {
                    'content-type': 'application/json' // 默认值
                },
                success: async (res) => {
                    await that.setData({
                        cabinet: res.data.cabinet,
                        show: false
                    })
                }
            })
        }
        req()
        setInterval(() => {
            req()
        }, 1000)


    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function () {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide: function () {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload: function () {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh: function () {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom: function () {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage: function () {

    }
})