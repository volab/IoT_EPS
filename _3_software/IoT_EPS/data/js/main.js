$(document).ready(()=>{
// start .ready()

const log = new C_MyLog();
const regEx = new C_RexExPatern();
const red = new C_Plug("redPlug");

/*
 * Nettoyage avant usage
 */
regEx.f_clean();
red.f_clean();

/*
 * Events Manuel
 */
$(red.modeManuel).on(
    "click", 
    ()=>{
        regEx.f_clean();
        red.f_displayManuelDiv("block");
    }
);

$(red.manuelON).on(
    "click",
    ()=>{
        red.f_displayTypeSelector("block"); 
    }
);

$(red.manuelOFF).on(
    "click",
    ()=>{
        red.f_displayTypeSelector("none"); 
        red.f_displayDiv_dureeOff("none");
        red.f_displayDiv_hFin("none");
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
        regEx.f_clean();
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
        regEx.f_clean();
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
        let inputJQSelector = $("input.redPlug.Cyclique").not(".pause").not($(red.modeCyclique));
        if ($(red.cycliquePause).is(":checked")){
            red.f_toggleCycliquePauseBool();
            inputJQSelector.each((i)=>{
                inputJQSelector[i].disabled=true;
            });
        } else {
            red.f_toggleCycliquePauseBool();
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
        if (!red.cycliquePauseBool){
            $(red.cycliqueForm)[0].reset();
        }
    }
);

/* 
 * event Hebdomadaire
 */

$(red.modeHedbomadaire).on(
    "click", 
    function(){
        regEx.f_clean();
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
        let inputJQSelector = $("input.redPlug.Hebdomadaire").not(".pause").not($(red.modeHedbomadaire));
        if ($(red.hebdomadairePause).is(":checked")){
            red.f_toggleHebdomadairePauseBool();
            inputJQSelector.each((i)=>{
                inputJQSelector[i].disabled=true;
            });
        } else {
            red.f_toggleHebdomadairePauseBool();
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
        if (!red.hebdomadairePauseBool){
            $(red.hebdomadaireForm)[0].reset();
        }
    }
);

/* 
 * event Clone
 */

$(red.modeClone).on(
    "click", 
    (event)=>{
        regEx.f_clean();
        red.f_cloneHideCurrentPlug(event);
        red.f_displayCloneDiv("block");
    });

$(red.cloneToRed).on(
    "click",
    (event)=>{
    event.preventDefault();
    $(red.cloneInputHide).val("redPlug");
    $(red.cloneForm).submit();
    }
)

$(red.cloneToGreen).on(
    "click",
    (event)=>{
    event.preventDefault();
    $(red.cloneInputHide).val("greenPlug");
    $(red.cloneForm).submit();
    }
)

$(red.cloneToBlue).on(
    "click",
    (event)=>{
    event.preventDefault();
    $(red.cloneInputHide).val("bluePlug");
    $(red.cloneForm).submit();
    }
)

$(red.cloneToYellow).on(
    "click",
    (event)=>{
    event.preventDefault();
    $(red.cloneInputHide).val("yellowPlug");
    $(red.cloneForm).submit();
    }
)

// $(red.cloneSubmit).on(
//     "click",
//     (event)=>{
//         console.log("envoyer");
//         console.log( $(red.cloneSelector).val() );
//         console.log( red.CloneForm );
//         $(red.cloneForm).submit();
//     }
// );

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
 * #. Finir les fonction "clear". Les appliquer sur chaque chagement de mode, changement de prise
 *    et entre chaque action du mode manuel
 *
 * ####
 *
 * #. Chagement de class automatique
 * 
 * ####
 *
 * #. Ajouter un fieldset de résumé de l'état des prises
 *    /!\ tenir compte de l'état du boutons pause dans le JSON lors du chargement
 *        des modes Cyclique et Hebdomadoare
 * 
 * ####
 *  
 * #. Gestion de la transition entre les DIV (jqueryui .effect "drop" et "slide")
 * 
 * ####
 * 
 * #. Navigation responcive (navbar et menu selector)
 * 
 * ####
 * 
 * #. Ajouter un fieldset ou un div pour l'aide
 *    ==> ne plus utiliser la page "help.html"
 * 
 *  ####
 * 
 * #. Ajouter un fieldset ou un div pour la personnalisation
 *    (toujours sur la même page)
 * 
 * ## TODO
 */
