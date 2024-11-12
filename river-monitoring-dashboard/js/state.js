document.addEventListener("DOMContentLoaded", ()=>{
    const stateIndex = "";
    const field = document.getElementById("state");
    function checkState(){
        fetch(stateIndex)
            .then(response => response.text)
            .then(text=>{
                if(field!=null){
                    field.innerText = text;
                }
            });
    }
    setInterval(checkState,5000);
})