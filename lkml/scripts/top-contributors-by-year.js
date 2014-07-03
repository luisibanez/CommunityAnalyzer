var db = connect("mongo/xdata");

var n = 10;

var map = function () {
    emit({
        year: this._id.year,
        from: this._id.from
    }, this.value);
};

var reduce = function (key, values) {
    return Array.sum(values);
};

var recs = db.lkml.contributors.mapReduce(map, reduce, {
    out: {
        inline: 1
    }
}).results;

printjson(recs);
