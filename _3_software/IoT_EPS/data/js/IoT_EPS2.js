var l_plug = ["redPlug", "greenPlug", "bluePlug", "yellowPlug"];
var l_mode = ["Manuel", "Minuterie", "Cyclique", "Hebdomadaire", "Clone"];

var v_div_subSummary = document.getElementsByClassName('div_subSummary');
var v_forTarget = v_div_subSummary.length;
//console.log(v_forTarget);


var v_diffSelector = document.getElementById("rdiv_DiffSelector");
var v_divDiffAt = document.getElementById("rDivDiffAt");
var v_divDiffIn = document.getElementById("rDivDiffIn");

var v_redManuel = document.getElementById("rManuel");
var v_rRdOn = document.getElementById("rRdOn");
var v_rRdOff = document.getElementById("rRdOff");
var v_divDiffSelector = document.getElementsByClassName ("redPlug div_DiffSelector");
var v_rRdDiffAt = document.getElementById("rRdDiffAt");
var v_rRdDiffIn = document.getElementById("rRdDiffIn");

var v_redSubmit = document.getElementById("redSubmit");

/* Fonction de masquage de tous les éléments */
function f_displayNoneAll(){
    for (var i=0; i < v_forTarget; i++) {
        v_div_subSummary[i].style.display="none";
    }
    document.getElementsByClassName("redPlug Manuel")[0].style.display="none";
    v_diffSelector.style.display="none";
    v_divDiffAt.style.display="none";
    v_divDiffIn.style.display="none";

    v_rRdDiffAt.checked = false;
    v_rRdDiffIn.checked = false;
}

f_displayNoneAll();

/* Mode Manuel : onclick */
v_redManuel.onclick = function (){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug Manuel")[0].style.display="block";
    }

v_rRdOn.onclick = function(){
    v_diffSelector.style.display = "block"; 
    console.log("marche");
    }

v_rRdOff.onclick = function(){
    v_diffSelector.style.display = "none";
    v_divDiffIn.style.display = "none";
    v_divDiffAt.style.display = "none";
    console.log("Arrêt");
    }

v_rRdDiffAt.onclick = function(){
    v_divDiffAt.style.display = "block";
    v_divDiffIn.style.display = "none";
}

v_rRdDiffIn.onclick = function(){
    v_divDiffIn.style.display = "block";
    v_divDiffAt.style.display = "none";
}

v_redSubmit.onclick = function(){
    document.getElementById("formMA").submit();
    document.getElementById("formMA").reset();
    }

/* Mode Minuterie */
var v_redMinuterie = document.getElementById("rMinuterie");

v_redMinuterie.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Minuterie")[0].style.display="block";
}

/* Mode Cyclique */
var v_redCyclique = document.getElementById("rCyclique");

v_redCyclique.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Cyclique")[0].style.display="block";
}

// document.getElementById("id_redNumOnCyclique")

/* Mode Hebdomadaire */
var v_redHebdo = document.getElementById("rHebdo");

v_redHebdo.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Hebdomadaire")[0].style.display="block";
}

var v_daySelector = document.querySelectorAll(".redPlug .daySelector");
v_daySelector[0].addEventListener("click", function(event){ 
    if (v_daySelector[0].checked){ 
        for (var i=1; i<(v_daySelector.length); i++){
            v_daySelector[i].checked = true;
        }} }, false);


var v_weekDay = document.querySelector(".redPlug .Hebdomadaire .weekDay")
v_weekDay.addEventListener("click", function(event){
    if (!event.target.checked){
        v_daySelector[0].checked = false;
    }
}, false);
        

/* Mode Clone */
var v_redClone = document.getElementById("rClone");

v_redClone.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Clone")[0].style.display="block";
}


// code permettant de cocher (checked) un éléments 
/*
document.getElementById('_1234').checked = true;
*/


// Code de validation du format pour les durées (pour le mode Minuterie)
/*
var v_regExDuree = /^(300|[0-2]{0,1}\d{0,2}|300:00|[0-2]{0,1}\d{0,2}:[0-5]\d{1})$/;
    // /!\Attention/!\:
    //      - les minutes sont comprises entre 0 et 300
    //      - les secondes sont comprises entre 0 et 59
    //          --> si les minutes sont égales à 300, les secondes doivent être égale à 0

var dOn = document.getElementsByClassName("redPlug Minuterie dureeOn"); 
    // attention il sagit d'un Objet, pas d'un tableau.
    // On ne peut donc pas faire de "foreach" dessus, mais seulement un "for"

dOn[0].addEventListener("input", function(event){
    if (regExDuree.test(dOn[0].value)){
        console.log("True");
    } else {
        console.log("format non valide");
    }
}, false);
*/


/* /!\Attention/!\ */ 
// Le format de durée pour le mode Manuel et pour le mode Cyclique est sur 3 digit, pas de secondes
/*
var regExDureeNoSec = /^(300|[0-2]{0,1}\d{0,2})$/;
    // /!\Attention/!\:
    //      - les minutes sont comprises entre 0 et 300
*/


// Code de validation du format pour les heures
/*
var regExHeure = /^([0-2]{0,1}\d{1}:[0-5]\d{1})$/;
    // /!\Attention/!\:
    //      - Les heures sont comprises entre 0 et 23
    //      - Les minutes sont comprises entre 0 et 59
*/