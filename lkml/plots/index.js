/*jslint browser: true */
/*globals vg, d3 */

var data = {};

function barchartSpec() {
    "use strict";

    var spec = {
        "width": 400,
        "height": 200,
        "padding": {"top": 10, "left": 60, "bottom": 30, "right": 10},
        "data": [
            {
                "name": "table",
                "values": undefined
            }
        ],
        "scales": [
            {
                "name": "x",
                "type": "ordinal",
                "range": "width",
                "domain": {"data": "table", "field": "data.x"}
            },
            {
                "name": "y",
                "range": "height",
                "nice": true,
                "domain": {"data": "table", "field": "data.y"}
            }
        ],
        "axes": [
            {"type": "x", "scale": "x"},
            {"type": "y", "scale": "y"}
        ],
        "marks": [
            {
                "type": "rect",
                "from": {"data": "table"},
                "properties": {
                    "enter": {
                        "x": {"scale": "x", "field": "data.x"},
                        "width": {"scale": "x", "band": true, "offset": -1},
                        "y": {"scale": "y", "field": "data.y"},
                        "y2": {"scale": "y", "value": 0}
                    },
                    "update": {
                        "fill": {"value": "steelblue"}
                    },
                    "hover": {
                        "fill": {"value": "red"}
                    }
                }
            }
        ]
    };

    //spec.data.values = values;
    return spec;
}

function refresh(spec, values) {
    "use strict";

    vg.parse.spec(spec, function (chart) {
        d3.select("#vis")
            .selectAll("*")
            .remove();

        chart({
            el: "#vis",
            data: {
                table: values
            }
        }).update();
    });
}

window.onload = function () {
    "use strict";

    d3.select("#update")
        .on("click", function () {
            var dataset,
                filter;
       
            dataset = d3.select("#datasets")
                .property("value");

            filter = d3.select("#filter")
                .property("value");
                

            if (filter.trim() !== "") {
                try {
                    filter = eval("(" + filter + ")");
                } catch(e) {
                    console.warn("error: could not parse filter function");
                    console.warn(e);
                    return;
                }
            } else {
                filter = function (x) { return x; };
            }

            refresh(barchartSpec(), data[dataset].filter(filter));
        });


    d3.json("month.json", function (e1, month) {
        d3.json("day.json", function (e2, day) {
            d3.json("hour.json", function (e3, hour) {
                d3.json("minute.json", function (e4, minute) {
                    data.month = month;
                    data.day = day;
                    data.hour = hour;
                    data.minute = minute;

                    refresh(barchartSpec(), day);
                });
            });
        });
    });
};
