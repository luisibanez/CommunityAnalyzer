var db = connect("mongo/xdata");

var answerStats = db.lkml.group({
    cond: {
        "In-Reply-To": {
            $exists: false
        }
    },
    keyf: function (u) {
        return {
            "month": u["Date"].getMonth(),
            "year": u["Date"].getFullYear()
        };
    },
    reduce: function (cur, result) {
        if (cur.response_time === undefined) {
            result.unanswered += 1;
        } else {
            result.answered += 1;
        }
    },
    initial: {
        unanswered: 0,
        answered: 0
    }
});

var answerRate = db["lkml.answerRate"];
answerRate.drop();
answerRate.insert(answerStats);
