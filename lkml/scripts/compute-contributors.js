var db = connect("mongo/xdata");

var map = function () {
    emit({
        month: this.Date.getMonth(),
        year: this.Date.getFullYear(),
        from: this.From
    }, 1);
};

var reduce = function (key, values) {
    return values.reduce(function (a, b) {
        return a + b;
    });
}

db.lkml.mapReduce(map, reduce, {
    out: "lkml.contributors"
});
