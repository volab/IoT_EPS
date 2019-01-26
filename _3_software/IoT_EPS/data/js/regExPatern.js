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
        for (let i=0; i<2; i++){
            v_tmp += "." + v_targetClassList[i];
        }
        this.v_classList = v_tmp
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
            for (let i=2; i<v_targetClassList.length; i++){
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
            v_target.css("border", "2px solid red");
            v_submit.disabled = true;
        } else if (v_regEx.test(v_target.val())){
            v_target.css("border", "2px solid green");
            v_submit.disabled = false;
            this.v_validInput = true;
        }
    }

    f_compare(event, v_targetToCompare, v_isEqual){
        /* Permet de comparer la valeur actuel à celle d'un autre éléments.
         * 
         * Les éléments atendu sont
         *  - event : l'événements qui a générer l'appel de la fonction
         *  - v_targetToCompare : La cible de l'élément contenant l'élément à comparer
         *  - v_isEqual (Boolean): permet de définir si la valeur à comparer doit être égale ou diférente
         *      true    --> la valeur comparée doit être égale
         *      false   --> la valeur comparée doit être diférente
         */ 
        this.f_getClassMode(event);
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
}