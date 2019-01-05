const log = new C_MyLog();
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
        red.manuelSubmit.disabled = false;
    },
    false);    

red.manuelDiffAt.addEventListener(
    "click",
    function(){
        red.f_displayDiv_hFin("block");
        red.f_displayDiv_dureeOff("none");
    },
    false);    

 red.manuelDiffIn.addEventListener(
    "click",
    function(){
        red.f_displayDiv_hFin("none");
        red.f_displayDiv_dureeOff("block");
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

red.manuelForm.addEventListener(
    "submit",
    function(event){
        log.f_formLog( red.f_getQueryTarget(event));
        red.manuelForm.submit();
        red.manuelForm.reset();
    },
    false);


/*
 * Events Minuterie
 */
red.modeMinuterie.addEventListener(
    "click", 
    function(){
        red.f_displayMinuterieDiv("block");
    },
    false);

red.minuterie_dureeOn.addEventListener(
    "input",
    function(event){
        regEx.f_callbackRegEx(event)},
        false);

red.minuterieForm.addEventListener(
    "submit",
    function(event){
        log.f_formLog( red.f_getQueryTarget(event));
        red.minuterieForm.submit();
        red.minuterieForm.reset();
    },
    false);