var db = connect("mongo/xdata");

var recs = db.lkml.answerTime.find()
    .sort({
        year: 1,
        month: 1
    });

var data = {};

recs.forEach(function (u) {
    if (data[u.year] === undefined) {
        data[u.year] = {
            time: 0,
            count: 0
        };
    }

    data[u.year].time += u.mean_response_time * u.count;
    data[u.year].count += u.count;
});

var years = Object.keys(data);
years.sort();

print('"Year", "Mean Response Time"');
years.forEach(function (y) {
    print(y + ", " + data[y].time / data[y].count);
});
