class C_RexExPatern{
    constructor(){
        // regEx
        this.v_regExDuree       = /^(300|[0-2]{0,1}\d{1,2}|300:00|[0-2]{0,1}\d{0,2}:[0-5]\d{1})$/;
            // /!\Attention/!\:
            //      - les minutes sont comprises entre 0 et 300
            //      - les secondes sont comprises entre 0 et 59
            //          --> si les minutes sont égales à 300, les secondes doivent être égale à 0
        this.v_regExDureeNoSec  = /^(300|[0-2]{0,1}\d{1,2})$/;
            // /!\Attention/!\ 
            // Le format de durée pour le mode Manuel et pour le mode Cyclique est sur 3 digit, pas de secondes
            //      - les minutes sont comprises entre 0 et 300

        this.v_regExHeure       = /^([0-2]{0,1}\d{1}:[0-5]\d{1})$/;
            // /!\Attention/!\:
            //      - Les heures sont comprises entre 0 et 23
            //      - Les minutes sont comprises entre 0 et 59

        // Définission des varriables génériques
        this.v_classList        = null;
        this.v_targetClass      = null;
        this.v_validInput       = true;

        // Définission des éléments cibles (querySelect)
        this.queryTarget        = null;
        this.queryCompare       = null;
        this.querySubmit        = null;
    }

    f_getClassMode(event){
        /* Permet de définir la variable 'v_classList' en récupérant les 2 premières class
         * depuis: 'event.target.classList'
         */
        let v_targetClassList = (event.target.classList);
        let v_tmp = "";
        // for (let i=0; i<2; i++){
        for (let i=0; i<1; i++){
            v_tmp += "." + v_targetClassList[i];
        }
        this.v_classList = v_tmp;
    }

    f_querySelect(event, target){
        /* Permet de définir les éléments cibles provenant du champs 'input' source
         * et recupérant le 'Submit' associer.
         *
         * Les éléments attendu sont:
         *  - event : l'événements qui a générer l'appel du callback
         *  - target : ('input', ou 'submit') pour définir le type du querySelector à définir
         */
        this.f_getClassMode(event);
        let v_targetClassList = (event.target.classList);
        let v_tmp = this.v_classList;
        if (target === "input") {
            // for (let i=2; i<v_targetClassList.length; i++){
            for (let i=1; i<v_targetClassList.length; i++){
                v_tmp += "." + v_targetClassList[i];
            }
            this.queryTarget = $(v_tmp);
        } else if (target === "submit") {
            v_tmp += ".submit";
            this.querySubmit = $(v_tmp)[0];
        }
    }

    f_callbackRegEx(event){
        /* Permet de comparer la valeur saisie dans l'élément 'input' au motif du regEx (patern)
         * Si les deux éléments ne correspondent pas la bodure extérieur passe en rouge et
         * le bouton 'submit' et désactivé
         * 
         * Les éléments attendu sont:
         *  - event : l'événements qui a générer l'appel de la fonction
         */ 
        let v_regEx = null;

        this.f_querySelect(event, "input");
        this.f_querySelect(event, "submit");
        this.f_compare(event, false);
        let v_target = this.queryTarget;
        let v_submit = this.querySubmit;
        
        // Selection du patern
        if (v_target.hasClass("patern_heure")){
            v_regEx = this.v_regExHeure;
        }  else if (v_target.hasClass("patern_dureeNoSec")){
            v_regEx = this.v_regExDureeNoSec;
        } else if (v_target.hasClass("patern_duree")){
            v_regEx = this.v_regExDuree;
        }

        // comparaison du patern
        if (!v_target.val()){
            v_submit.disabled = false;
        } else if (!v_regEx.test(v_target.val()) || !this.v_validInput) {
            v_target.css({
                "border": "4px solid #ff3300",
                "box-shadow": "0 0 10px 5px #ff3300"
                });
            v_submit.disabled = true;
            this.f_errMsg(v_target, true);
            this.v_validInput = true;
        } else if (v_regEx.test(v_target.val())){
            // v_target.css("border", "2px solid green");
            v_target.css({
                "border": "4px solid #33cc33",
                "box-shadow": "0 0 10px 5px #33cc33"
            });
            v_submit.disabled = false;
            this.v_validInput = true;
            this.f_errMsg(v_target, false);
        }
    }

    f_compare(event, v_isEqual, v_target1="hDebut", v_target2="hFin"){
        /* Permet de comparer la valeur actuel à celle d'un autre éléments.
         * 
         * Les éléments atendu sont
         *  - event : l'événements qui a générer l'appel de la fonction
         * 
         *  - v_target1 et v_target2 : représentent la source (le champ actif dans lequel la saisie
         *    est effectuée) et la cible (l'élément dont la valeur sera comparée à celle de la source).
         *    * Si 'v_target1' est identifié comme source, 'v_target2' deviendra la cible.
         *    * Si 'v_target2' est identifié comme source, 'v_target1' deviendra la cible.
         * 
         *  - v_isEqual (Boolean): permet de définir si la valeur à comparer doit être égale ou diférente
         *      true    --> la valeur comparée doit être égale
         *      false   --> la valeur comparée doit être diférente
         */
        let v_targetToCompare = null;
        if ($(event.target).hasClass(v_target1)){
            v_targetToCompare = v_target2;
        } else if ($(event.target).hasClass(v_target2)){
            v_targetToCompare = v_target1;
        }

        let v_target = $(`${this.v_classList}.${v_targetToCompare}`);

        if (v_isEqual){
            if (!(v_target.val() == event.target.value)){
                this.v_validInput = false;
                // console.log("Diférent, c'est pas bien !");
            } 
        } else if (!v_isEqual) {
            if (v_target.val() == event.target.value){
                this.v_validInput = false;
                // console.log("Identique, c'est pas bien !");
            } 
        }
    }

    f_errMsg(v_target, v_showSpan){
        /* Affiche (ou masque) les messages d'erreur de saisie pour les champs "hDebut",
         * "hFin", "dureeOn" et "dureeOff". 
         *
         * Les éléments attentdu sont :
         *   - v_target : L'élément ciblé par event (this.querytarget)
         *   - v_showSpan (boolean) : pour définir si la visibilité de l'élément 'span' est Vrai ou Faut
         */ 

        if (!v_target.val()){
            // console.log(`valeur vide`);
            return false;
        }

        // console.log(`f_errMsg:v_taget :${v_target.val()}`);

         let v_inputType    = null;
         let v_errMsg       = null;

        if (v_showSpan) {
            if ((v_target.attr("name")=="hDebut")||(v_target.attr("name")=="hFin")) {
                v_inputType = "heure";
            } else if (v_target.hasClass("Minuterie")) {
                v_inputType = "Minuterie";
            } else {
                v_inputType = "duree";
            }

            // Définission du message d'erreur
            if (!this.v_validInput) {
                v_errMsg = `L'heure de fin ne peut pas être la même que l'heure de début`;
            } else if (v_inputType == "heure") {
                v_errMsg = `L'heure doit être indiquée sous la forme 'HH:MM'`;
            } else if (v_inputType == "Minuterie") {
                v_errMsg = `La durée doit être indiquée sous la forme 'MMM' ou 'MMM:SS'`;
            } else if (v_inputType == "duree") {
                v_errMsg = `La durée doit être indiquée sous la forme 'MMM'`;
            }
            $("body").append(
                `<div class="infobulle alert alert-danger alert-dismisible fade show">
                </div>`);
            let bulle = $(".infobulle");
            bulle.text(v_errMsg);
            let v_topPos = v_target.offset().top-v_target.height();
            let v_leftPos = v_target.offset().left+v_target.width()/2-bulle.width()/2;
            bulle.css({
                left:v_leftPos,
                top:v_topPos
            });
        } else {
            $(".infobulle").remove();
        }
    }

    f_clean(){
        /* Permet de supprimer les éléments visuel ajoutés lors de la vérification des valeurs saisies */
        $(".infobulle").remove();
        $("input[type='text']").css("border", "none");
    }
}