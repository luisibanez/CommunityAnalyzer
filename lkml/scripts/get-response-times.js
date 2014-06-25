var db = connect("mongo/xdata");

var thread_orig = db.lkml.find({
    "In-Reply-To": {
        $exists: false
    }
});

var responded = db.lkml.find({
    response_time: {
        $exists: true
    }
}, {response_time: 1});

print(thread_orig.count() + " thread-originating emails");
print(responded.count() + " with responses");

var response_times = responded.map(function (u) {
    return u.response_time;
});

printjson(response_times);
