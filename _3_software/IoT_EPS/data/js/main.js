const regEx = new C_RexExPatern();
const red = new C_Plug("redPlug");


/*
 * Events Manuel
 */
red.modeManuel.addEventListener(
    "click", 
    function(){
        red.f_displayManuelDiv("block");
    },
    false);

red.manuelON.addEventListener(
    "click",
    function(){
        red.f_displayTypeSelector("block"); 
    },
    false);

red.manuelOFF.addEventListener(
    "click",
    function(){
        red.f_displayTypeSelector("none"); 
        red.f_displayDiv_dureeOff("none");
        red.f_displayDiv_hFin("none");
    },
    false);    

red.manuelDiffAt.addEventListener(
    "click",
    function(){
        red.f_displayDiv_hFin("block");
        red.f_displayDiv_dureeOff("none");
        red.manuelDiffIn.checked = false;
    },
    false);    

 red.manuelDiffIn.addEventListener(
    "click",
    function(){
        red.f_displayDiv_hFin("none");
        red.f_displayDiv_dureeOff("block");
        red.manuelDiffAt.checked = false;
    },
    false);

red.manuel_hFin.addEventListener(
    "input",
    function(event){
        regEx.f_callbackRegEx(event)},
        false);

red.manuel_dureeOff.addEventListener(
    "input",
    function(event){
        regEx.f_callbackRegEx(event)},
        false);