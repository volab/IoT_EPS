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
    }

    f_callbackRegEx(event){
        let v_targetClassList = (event.target.classList);
        let v_tmp = "";
        let v_regEx = null;
        for (let i=0; i<v_targetClassList.length; i++){
            v_tmp += "." + v_targetClassList[i];
        }
        
        let v_target = document.querySelector(v_tmp);
        
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
        } else {
        v_target.style.border="2px solid red";
        }
    }    
}