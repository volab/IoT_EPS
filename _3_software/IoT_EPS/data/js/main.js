$(document).ready(()=>{
// start .ready()

const log = new C_MyLog();
const regEx = new C_RexExPatern();
const red = new C_Plug("redPlug");


/*
 * Events Manuel
 */
$(red.modeManuel).on(
    "click", 
    ()=>{
        red.f_displayManuelDiv("block");
    }
);

$(red.manuelON).on(
    "click",
    ()=>{
        red.f_displayTypeSelector("block"); 
        $(red.manuelSubmit)[0].disabled = false;
    }
);

$(red.manuelOFF).on(
    "click",
    ()=>{
        red.f_displayTypeSelector("none"); 
        red.f_displayDiv_dureeOff("none");
        red.f_displayDiv_hFin("none");
        red.manuelSubmit[0].disabled = true;
        red.manuelForm.submit();
        red.manuelOFF[0].checked=true;
    }
);

$(red.manuelDiffAt).on(
    "click",
    ()=>{
        red.f_displayDiv_hFin("block");
        red.f_displayDiv_dureeOff("none");
    }
);    

$(red.manuelDiffIn).on(
    "click",
    ()=>{
        red.f_displayDiv_hFin("none");
        red.f_displayDiv_dureeOff("block");
    }
);

$(red.manuel_hFin).on(
    "input",
    (event)=>{
        regEx.f_callbackRegEx(event)
    }
);

$(red.manuel_dureeOff).on(
    "input",
    (event)=>{
        regEx.f_callbackRegEx(event)
    }
);

$(red.manuelForm).on(
    "submit",
    (event)=>{
        event.preventDefault();
        $(this).submit();
        log.f_formLog( red.f_getQueryTarget(event));
        $(red.manuelForm)[0].reset();
    }
);

/*
 * Events Minuterie
 */
$(red.modeMinuterie).on(
    "click", 
    ()=>{
        red.f_displayMinuterieDiv("block");
    });

$(red.minuterie_dureeOn).on(
    "input",
    (event)=>{
        regEx.f_callbackRegEx(event)
    });

$(red.minuterieForm).on(
    "submit",
    (event)=>{
        event.preventDefault();
        $(this).submit();
        log.f_formLog( red.f_getQueryTarget(event));
        $(red.minuterieForm)[0].reset();
    }
);

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

/*
 * ## TODO
 *
 * #. Dans le mode Hebdomadaire, faire en sorte que l'heure de fin ne puisse pas être la 
 *    même que l'heure de début
 * 
 * ####
 * 
 * #. Mode Clone: desactiver le selecteur de la prise courante 
 *    (ex: désactiver la prise rouge si on est ds la prise rouge).
 * 
 * ####
 * 
 * #. Chagement de class automatique
 * 
 * ####
 *
 * #. Ajouter un fieldset de résumé de l'état des prises
 * 
 * ####
 *  
 * #. Gestion de la transition entre les DIV (jqueryui .effect "drop" et "slide")
 * 
 * ####
 * 
 * #. Navigation responcive (navbar et menu selector)
 * 
 * ## TODO
 */