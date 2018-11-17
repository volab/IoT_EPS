var v_jsonFile = 'config2.json';

/* 
 * la fonction loadJson à été piqué ici:
 * http://www.askyb.com/javascript/load-json-file-locally-by-js-without-jquery/comment-page-1/#comment-4130
 */
 function f_loadJSON(v_file, callback) { 
    var xobj = new XMLHttpRequest();
    xobj.overrideMimeType("application/json");
    xobj.open('GET', v_file, true);
    xobj.onreadystatechange = function () {
       if (xobj.readyState == 4 && xobj.status == "200") {
          callback(xobj.responseText);
       }
    }
    xobj.send(null);
}
    
f_loadJSON(v_jsonFile, function(response) {
    jsonresponse = JSON.parse(response);

    /* general */
    var v_hostname = jsonresponse["general"]["hostName"];
    // generation automatique du Titre (dans l'onglet) et du H1 de index.html
    document.getElementById("autoTitle").innerHTML=v_hostname;
    document.getElementById("autoH1").innerHTML=v_hostname;

    /* redPlug */
    var v_rState = jsonresponse["redPlug"]["State"];
    var v_rManuel = jsonresponse["redPlug"]["Manuel"];
    var v_rMinuterie = jsonresponse["redPlug"]["Minuterie"];
    var v_rCyclique = jsonresponse["redPlug"]["Cylcique"];
    var v_rHebdo = jsonresponse["redPlug"]["Hebdomadaire"];

    if (v_rManuel["Status"] == "ON"){
        console.log("Manuel");
        var v_rStatus = document.getElementById("rStatus");
        var v_h5 = document.createElement('h3');
        v_h5.textContent = "Mode Manuel";
        rStatus.appendChild(v_h5);

    } else if (v_rMinuterie["Status"] == "ON"){
        console.log("Minuterie");
        var v_rStatus = document.getElementById("rStatus");
        var v_h5 = document.createElement("h5");
        var v_div = document.createElement("div");
        var v_statePlug = document.createElement("p");
        var v_timer = document.createElement("p");

        v_h5.textContent = "Mode Minuterie";
        v_statePlug.textContent = "La prise est : " + v_rState;
        v_timer.textContent = "La minuterie est réglée sur : " + v_rMinuterie["Duree"] + " min";
        rStatus.appendChild(v_h5);
        rStatus.appendChild(v_statePlug);
        rStatus.appendChild(v_timer);

    } else if (v_rCyclique["Status"] == "ON"){
        console.log("Cyclique");
        var v_rStatus = document.getElementById("rStatus");
        var v_h5 = document.createElement('h5');
        v_h5.textContent = "Mode Cyclique";
        rStatus.appendChild(v_h3);

    } else if (v_rHebdo["Status"] == "ON"){
        console.log("Hebdo");
        var v_rStatus = document.getElementById("rStatus");
        var v_h5 = document.createElement('h5');
        v_h5.textContent = "Mode Hebdomadaire";
        rStatus.appendChild(v_h3);

    } else {

    }


    console.log(jsonresponse["redPlug"]);
    /* TODO: parcourir le fichier config2.json et l'aficher dans chaque
     * prise correspondante
     */
});
