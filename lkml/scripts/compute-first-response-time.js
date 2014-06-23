var db = connect("mongo/xdata");

// Get the set of emails that are not responses to another email.
var orig = db.lkml.find({
    "In-Reply-To": {
        $exists: false
    }
});

// For each such email, find the response email (if it exists).
print(orig.count() + " thread-originating emails");

var i = 0;
orig.forEach(function (u) {
    "use strict";

    i += 1;
    var reply = db.lkml.find({
        "In-Reply-To": u["Message-ID"]
    })
        .sort({"Date": 1});

    if (reply.count() > 0) {
        reply = reply.next();
        db.lkml.update({
            _id: u._id
        },
        {
            $set: {
                response_time: (reply["Date"] - u["Date"]) / 1000
            }
        });
    }

    if (i % 1000 === 0) {
        print ("processed " + i + " records");
    }
});
