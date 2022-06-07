const mongoose = require('mongoose');
mongoose.connect('mongodb://10.0.12.4:27017/smartUsers', { useMongoClient: true });
let Schema = mongoose.Schema
let userSchema = new Schema({
    username: {
        type: String,
        required: true
    },
    password: {
        type: String,
        required: true
    },
    create_time: {
        type: Date,
        default: Date.now
    },
    //药房信息
    cabinet: [],
    //取药记录
    record: [],
    //要取的药品
    actionlattice: []  //[  [1],[2], ]
})

module.exports = mongoose.model('smartUser', userSchema);
