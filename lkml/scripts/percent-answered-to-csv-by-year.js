var db = connect("mongo/xdata");

var recs = db.lkml.answerRate.find();
var data = {};

recs.forEach(function (u) {
    if (data[u.year] === undefined) {
        data[u.year] = {
            answered: 0,
            unanswered: 0
        };
    }

    data[u.year].answered += u.answered;
    data[u.year].unanswered += u.unanswered;
});

var years = Object.keys(data);
years.sort();

print('"Year", "Answered", "Unanswered"');
years.forEach(function (y) {
    print(y + ", " + data[y].answered + ", " + data[y].unanswered);
});
