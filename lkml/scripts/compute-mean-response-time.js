var db = connect("mongo/xdata");

var answerTimes = db.lkml.group({
    cond: {
        "response_time": {
            $exists: true
        }
    },
    keyf: function (u) {
        return {
            "month": u["Date"].getMonth(),
            "year": u["Date"].getFullYear()
        };
    },
    reduce: function (cur, result) {
        result.mean_response_time += cur.response_time;
        result.count += 1;
    },
    initial: {
        mean_response_time: 0,
        count: 0
    },
    finalize: function (result) {
        result.mean_response_time /= result.count;
    }
});

var answerTime = db["lkml.answerTime"];
answerTime.drop();
answerTime.insert(answerTimes);
