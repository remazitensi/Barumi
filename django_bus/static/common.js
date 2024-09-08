var DELAY = 700, clicks = 0, timer = null;

$(function () {
    $("button")
        .on("dblclick", function (e) {
            e.preventDefault();  //cancel system double-click event
        });
});
/*
function speech(obj) {
    //one click
    var is = true;
    var utterThis = new SpeechSynthesisUtterance(obj.innerText);
     utterThis.lang= 'ko-KR';
    var synth = window.speechSynthesis;
    synth.speak(utterThis);
    console.log("work")
    return is;
}

 */
 const speech = function (node) {
        let text = node.innerText;
        text = encodeURIComponent(text);
        console.log(text)
        let url = "https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&total=1&idx=0&textlen=32&q=" + text + "&tl=ko-kr"
        console.log(url)
        $(node.parentNode.querySelector("audio")).attr('src', url).get(0).play();
    }
    const speechText = function (node,text){
     text = encodeURIComponent(text);
        console.log(text)
        let url = "https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&total=1&idx=0&textlen=32&q=" + text + "&tl=ko-kr"
        console.log(url)
        $(node.parentNode.querySelector("audio")).attr('src', url).get(0).play();
    }

function goto(place) {
    return location.href = place;
}