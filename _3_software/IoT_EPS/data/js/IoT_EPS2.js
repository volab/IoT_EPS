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

/* Mode Clone */
var v_redClone = document.getElementById("rClone");

v_redClone.onclick = function(){
    f_displayNoneAll();
    document.getElementsByClassName("redPlug div_subSummary Clone")[0].style.display="block";
}


/* code permettant de cocher (checked) un éléments */
//document.getElementById('_1234').checked = true;
