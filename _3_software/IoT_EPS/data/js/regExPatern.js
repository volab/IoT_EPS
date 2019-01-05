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

        // Définission des éléments cibles (querySelect)
        this.queryTarget        = null;
        this.querySubmit        = null;
    }

    f_querySelect(event, target){
        /* Permet de définir les éléments cibles pour provenant du champs 'input' source
         * et recupérant le 'Submit' associer.
         *
         * Les éléments attendu sont:
         *  - event : l'événements qui a générer l'appel du callback
         *  - target : ('input' ou 'submit') pour définir le type du querySelector à définir
         */
        let v_targetClassList = (event.target.classList);
        let v_tmp = "";
        if (target === "input") {
            for (let i=0; i<v_targetClassList.length; i++){
                v_tmp += "." + v_targetClassList[i];
            }
            this.queryTarget = document.querySelector(v_tmp);
        } else if (target === "submit") {
            for (let i=0; i<2; i++){
                v_tmp += "." + v_targetClassList[i];
            }
            v_tmp += ".submit";
            this.querySubmit = document.querySelector(v_tmp);
        }
    }

    f_callbackRegEx(event){
        /* Permet de comparer la valeur saisie dans l'élément 'input' au motif du regEx (patern)
         * Si les deux éléments ne correspondent pas la bodure extérieur passe en rouge et
         * le bouton 'submit' et désactivé
         */ 
        let v_regEx = null;

        this.f_querySelect(event, "input");
        this.f_querySelect(event, "submit");
        let v_target = this.queryTarget;
        let v_submit = this.querySubmit;
        
        if (v_target.classList.contains("patern_heure")){
            v_regEx = this.v_regExHeure;
        }  else if (v_target.classList.contains("patern_dureeNoSec")){
            v_regEx = this.v_regExDureeNoSec;
        } else if (v_target.classList.contains("patern_duree")){
            v_regEx = this.v_regExDuree;
        }
        
        //let v_regEx  = /^([0-2]{0,1}\d{1}:[0-5]{1}\d{1})$/;
        if (v_regEx.test(v_target.value)){
        v_target.style.border="2px solid green";
        v_submit.disabled = false;
        } else {
        v_target.style.border="2px solid red";
        v_submit.disabled = true;
        }
    }    
}