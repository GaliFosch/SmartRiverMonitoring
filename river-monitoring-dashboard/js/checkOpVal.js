document.addEventListener("DOMContentLoaded", ()=>{
    const opValIndex = "http://127.0.0.1:8000/gti/readOpVal";
    const openingField = document.getElementById("currentGateOpening");
    function checkUpdate(){
        let xhttp = new XMLHttpRequest()
        xhttp.onload = function () {
            let response = JSON.parse(xhttp.responseText)
            console.log(response)
            if (response){
                if(response["errorCode"] === 0){
                    openingField.innerText = "" + response["opVal"]
                }
            }
        }
        try {
            xhttp.open("GET", opValIndex, true)
            xhttp.send()   
        } catch (error) {
            console.log("ERROR: Error in checkOpVal")
            console.log(error)
        }
    }
    setInterval(checkUpdate,1000);
})