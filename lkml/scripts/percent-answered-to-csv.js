var db = connect("mongo/xdata");

var recs = db.lkml.answerRate.find()
    .sort({
        year: 1,
        month: 1
    });

var months = [
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
];

print('"Month", "Answered", "Unanswered"');
recs.forEach(function (u) {
    print('"' + months[u.month] + ' ' + u.year + '", ' + u.answered + ", " + u.unanswered);
});
