function getFalafel(callback) {
    const falafel = "Falafel"
    console.log(falafel + " aus dem Kühlschrank geholt")
    callback(falafel);
}

function fryFalafel(falafel, callback) {
    setTimeout(function() {
        const friedFalafel = "Frittierte " + falafel
        console.log(falafel + " frittiert")
        callback(friedFalafel);
    }, 1000);
}

function getWrap(callback) {
    const wrap = "Wrap"
    console.log(wrap + " aus dem Schrank geholt")
    callback(wrap);
}

function assembleFalafelWrap(wrap, friedFalafel, callback) {
    const falafelwrap = "Falafel-Wrap"
    console.log(friedFalafel + " in " + wrap + " gewickelt")
    callback(falafelwrap);
}

function prepareFalafelWrap(callback) {
    getFalafel(function(falafel) {
        fryFalafel(falafel, function(friedFalafel) {
            getWrap(function(wrap) {
                assembleFalafelWrap(wrap, friedFalafel, callback);
            });
        });
    });
}

function serve(meal) {
    console.log(meal + " serviert")
}

prepareFalafelWrap(serve);

