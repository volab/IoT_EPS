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

/* Replissage des informations par prise */
function f_populatePlug(v_Plug){
    console.log(v_Plug);
    var v_summary;
    switch (v_Plug) {
        case "redPlug":
            v_summary = "rSummary";
            break;
        case "greenPlug":
            v_summary = "gSummary";
            break;
        case "bluePlug":
            v_summary = "bSummary";
            break;
        case "yellowPlug":
            v_summary = "ySummary";
            break;
    }

    var v_State = jsonresponse[v_Plug]["State"];
    var v_Manuel = jsonresponse[v_Plug]["Manuel"];
    var v_Minuterie = jsonresponse[v_Plug]["Minuterie"];
    var v_Cyclique = jsonresponse[v_Plug]["Cyclique"];
    var v_Hebdo = jsonresponse[v_Plug]["Hebdomadaire"];

    if (v_Manuel["Status"] == "ON"){
        console.log("Manuel");
        f_subPopManuel(v_summary, v_Manuel, v_State);

    } else if (v_Minuterie["Status"] == "ON"){
        console.log("Minuterie");
        f_subPopMinuterie(v_summary, v_Minuterie, v_State);

    } else if (v_Cyclique["Status"] == "ON"){
        console.log("Cyclique");
        f_subPopCyclique(v_summary, v_Cyclique, v_State);

    } else if (v_Hebdo["Status"] == "ON"){
        console.log("Hebdo");
        f_subPopHebdo(v_summary, v_Hebdo, v_State);
    } else {
        console.log("Mode inconnu");
    }
}

/* Fonction permettant de définir le titre (hx) des résumer de prise */
function f_hSummary(v_summary, v_hContent){
    var v_hType = "h5";
    var v_h = document.createElement(v_hType);
    v_h.textContent = v_hContent;
    return v_h;
}

/* Sous fonction pour le remplissage du mode Manuel */
function f_subPopManuel(v_summary, v_Manuel, v_State){
    var v_Status = document.getElementById(v_summary);
    var v_statePlug = document.createElement("p");
    v_hSummary = f_hSummary(v_Status, "Mode Manuel");
    v_Status.appendChild(v_hSummary);
}

/* Sous fonction pour le remplissage du mode Minuterie */
function f_subPopMinuterie(v_summary, v_Minuterie, v_State){
    var v_Status = document.getElementById(v_summary);
    var v_statePlug = document.createElement("p");
    var v_timer = document.createElement("p");

    v_hSummary = f_hSummary(v_Status, "Mode Minuterie");
    v_statePlug.textContent = "La prise est : " + v_State;
    v_timer.textContent = "La minuterie est réglée sur : " + v_Minuterie["Duree"] + " min";

    v_Status.appendChild(v_hSummary);
    v_Status.appendChild(v_statePlug);
    v_Status.appendChild(v_timer);
}


/* Sous fonction pour le remplissage du mode Cyclique */
function f_subPopCyclique(v_summary, v_Manuel, v_State){
    var v_Status = document.getElementById(v_summary);
    var v_statePlug = document.createElement("p");
    v_hSummary = f_hSummary(v_Status, "Mode Cyclique");
    v_Status.appendChild(v_hSummary);
}

/* Sous fonction pour le remplissage du mode Hebdomadaire */
function f_subPopHebdo(v_summary, v_Manuel, v_State){
    var v_Status = document.getElementById(v_summary);
    var v_statePlug = document.createElement("p");
    v_hSummary = f_hSummary(v_Status, "Mode Hebdomadaire");
    v_Status.appendChild(v_hSummary);
}
/* Permet de redéfinir le titre de l'onglet) */
function f_populateTitle( v_hostname ){
    console.log("f_populateTitle");
    var v_title = document.getElementById("autoTitle");
    v_title.textContent = v_hostname;
    
}

/* Permet de redéfinir le H1 d'index.html */
function f_populateH1( v_hostname ){
    console.log("f_populateH1");
    var v_h1 = document.getElementById("autoH1");
    v_h1.textContent = v_hostname;
}
    
f_loadJSON(v_jsonFile, function(response) {
    jsonresponse = JSON.parse(response);

    /* general */
    var v_hostname = jsonresponse["general"]["hostName"];
    //document.getElementById("autoTitle").innerHTML=v_hostname;
    //document.getElementById("autoH1").innerHTML=v_hostname;
    //
    //N.B: l'emploi de 'innerHTML' est déconseiller car il représente une faille de sécurité
    //potenciel.
    f_populateTitle(v_hostname);
    f_populateH1(v_hostname);


    f_populatePlug("redPlug");
    f_populatePlug("greenPlug");
    f_populatePlug("bluePlug");
    f_populatePlug("yellowPlug");
});
