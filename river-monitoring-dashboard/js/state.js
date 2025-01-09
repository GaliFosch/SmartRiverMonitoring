document.addEventListener("DOMContentLoaded", ()=>{
    const stateIndex = "http://127.0.0.1:8000/wtld/get-state/";
    const stateField = document.getElementById("state");
    console.log(stateField)
    function checkState(){
        let xhttp = new XMLHttpRequest()
        xhttp.onload = function () {
            let response = JSON.parse(xhttp.responseText)
            if (response){
                if(response["errorCode"] === 0){
                    console.log("State: " + response["state"])
                    stateField.innerText = "" + response["state"]
                }
            }
        }
        try {
            xhttp.open("GET", stateIndex, true)
            xhttp.send()   
        } catch (error) {
            console.log("ERROR: Error in state fetching")
        }
    }
    setInterval(checkState,1000);
})