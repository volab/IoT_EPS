$(document).ready(()=>{
// start .ready()

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

/*
 * Events Cyclique
 */
$(red.modeCyclique).on(
    "click", 
    function(){
        red.f_displayCycliqueDiv("block");
    });

$(red.cyclique_dureeOn).on(
    "input",
    function(event){
        regEx.f_callbackRegEx(event);
    });

$(red.cyclique_dureeOff).on(
    "input",
    function(event){
        regEx.f_callbackRegEx(event);
    });
        
$(red.cyclique_hDebut).on(
    "input",
    function(event){
        regEx.f_callbackRegEx(event);
    });

$(red.cycliquePause).on(
    "click",
    (event)=>{
        let inputJQSelector = $("input.redPlug.Cyclique").not(".pause");
        if ($(red.cycliquePause).is(":checked")){
            inputJQSelector.each((i)=>{
                inputJQSelector[i].disabled=true;
            });
        } else {
            inputJQSelector.each((i)=>{
                inputJQSelector[i].disabled=false;
            });
        }
        red.cycliqueForm.submit();
    }
);    

$(red.cycliqueForm).on(
    "submit",
    (event)=>{
        event.preventDefault();
        $(this).submit();
        log.f_formLog( red.f_getQueryTarget(event));
        $(red.cycliqueForm)[0].reset();
    }
);

/* 
 * event Hebdomadaire
 */

$(red.modeHedbomadaire).on(
    "click", 
    function(){
        red.f_displayHebdomadaireDiv("block");
    });

$(red.hebdmadaireAllDays).on(
    "click",
    (event)=>{
        let inputJQSelector = $("input.redPlug.daySelector").not(".AllDays");
        if ($(red.hebdmadaireAllDays).is(":checked")){
            inputJQSelector.each((i)=>{
                inputJQSelector[i].checked=true;
            });
        }
    }
);

$(red.hebdomadaireWeekDay).on(
    "click",
    (event)=>{
        if ($(red.hebdomadaireWeekDay).is(":checked")){
            red.hebdmadaireAllDays[0].checked=false;
        }
});

$(red.hebdomadaire_hDebut).on(
    "input",
    function(event){
        regEx.f_callbackRegEx(event);
    });

$(red.hebdomadaire_hFin).on(
    "input",
    function(event){
        regEx.f_callbackRegEx(event);
    });

$(red.hebdomadairePause).on(
    "click",
    (event)=>{
        let inputJQSelector = $("input.redPlug.Hebdomadaire").not(".pause");
        if ($(red.hebdomadairePause).is(":checked")){
            inputJQSelector.each((i)=>{
                inputJQSelector[i].disabled=true;
            });
        } else {
            inputJQSelector.each((i)=>{
                inputJQSelector[i].disabled=false;
            });
        }
        red.hebdomadaireForm.submit();
    }
);    

$(red.hebdomadaireForm).on(
    "submit",
    (event)=>{
        event.preventDefault();
        $(this).submit();
        log.f_formLog( red.f_getQueryTarget(event));
        $(red.hebdomadaireForm)[0].reset();
    }
);

/* 
 * event Clone
 */

$(red.modeClone).on(
    "click", 
    function(){
        red.f_displayCloneDiv("block");
    });

$(red.cloneSelector).on(
    "change",
    (event)=>{
        console.log( $(red.cloneSelector).val() );
    }
)    

$(red.cloneSubmit).on(
    "click",
    (event)=>{
        console.log("envoyer");
        console.log( $(red.cloneSelector).val() );
        console.log( red.CloneForm );
        $(red.cloneForm).submit();
    }
);

$(red.cloneForm).on(
    "submit",
    (event)=>{
        event.preventDefault();
        console.log("form Submit");
        $(this).submit();
        log.f_formLog( red.f_getQueryTarget(event));
        $(red.cloneForm)[0].reset();
    }
);

// .ready() end
});