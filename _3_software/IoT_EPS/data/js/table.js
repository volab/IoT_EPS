/**
 * Class permmetant de définir l'objet Table
 *
 * @class C_Table
 * 
 */
class C_Table{
    constructor(){
        this.jsonOBJ        = "";
        this.v_item         = "";
        this.v_tableColor   = "";
        this.v_pauseOn      = "";
        this.v_detail       = "";

        this.v_nicName      = "";
        this.v_emplacement  = "";
        this.v_state        = "";
        this.v_pause        = "";
        this.v_mode         = "";
        this.v_hDebut       = "";
        this.v_hFin         = "";
        this.v_dureeOn      = "";
        this.v_dureeOff     = "";
        this.v_Jours        = "";
        this.v_clonedPlug   = "";

        this.v_modeCloned   = "";

    }

    f_resetData(){
        /* Permet de réinitialiser toutes les variables de l'instances */
        this.jsonOBJ        = "";
        this.v_item         = "";
        this.v_tableColor   = "";
        this.v_pauseOn      = "";
        this.v_detail       = "";

        this.v_nicName      = "";
        this.v_emplacement  = "";
        this.v_state        = "";
        this.v_pause        = "";
        this.v_mode         = "";
        this.v_hDebut       = "";
        this.v_hFin         = "";
        this.v_dureeOn      = "";
        this.v_dureeOff     = "";
        this.v_Jours        = "";
        this.v_clonedPlug   = "";

        this.v_modeCloned   = "";
    }

    f_setJsonOB(jsonresponse){
        /* Permet de définir l'objet json (le ficier '.json' à parcourir) */
        this.jsonOBJ = jsonresponse;
    }

    f_setItem(firstItem){
        /* Permet de définir l'item de premier niveau à parcourrir dans le fichier '.json' */
        this.v_item = this.jsonOBJ[firstItem];
    }

    f_setRowColor(firstItem){
        /* 
         * Permet de définir la couleur de la ligne.
         * les couleurs sont identifiée par des class bootstrap
         */
        switch (firstItem){
            case "redPlug": {
                this.v_tableColor = "table-danger";
                break;}
            case "greenPlug": {
                this.v_tableColor = "table-success";
                break;}
            case "bluePlug": {
                this.v_tableColor = "table-primary";
                break;}
            case "yellowPlug": {
                this.v_tableColor = "table-warning";
                break;}
        }
    }

    f_setSubItem(){
        /* Permet de définir les différents sous éléments du fichier '.json' */
        this.v_nicName      = this.v_item["nickName"];
        this.v_emplacement  = this.v_item["emplacement"];
        this.v_state        = this.v_item["State"];
        this.v_pause        = this.v_item["Pause"];
        this.v_mode         = this.v_item["Mode"];
        this.v_hDebut       = this.v_item["hDebut"];
        this.v_hFin         = this.v_item["hFin"];
        this.v_dureeOn      = this.v_item["dureeOn"];
        this.v_dureeOff     = this.v_item["dureeOff"];
        this.v_Jours        = this.v_item["Jours"];
        this.v_clonedPlug   = this.v_item["clonedPlug"];
    }

    f_ifCloned(){
        /* Permet de définir 'v_modeCloned' */
        if (this.v_item["clonedPlug"]){
            let v_clonePlugName = this.jsonOBJ[this.v_clonedPlug]["nickName"];
            this.v_modeCloned = `<br>(prise clonée depuis la prise ${v_clonePlugName})`
        }
    }

    f_ifPause(){
        /*  Permet de définir 'v_pauseOn' */
        if ((this.v_mode=="Cyclique" || this.v_mode=="Hebdomadaire") && this.v_pause=="ON" && this.v_state=="ON"){
            this.v_pauseOn = `<br><span class="text-danger">Actuellement en PAUSE</span>`;
        }
    }

    f_dayList(){
        /* Permet de définir la liste des jours actifs. */
        let v_count = 0;
        let l_dayList = ["Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"];
        let v_renderList = `<ul>`;
        for (let i of this.v_Jours){
            if (i=="ON"){
                v_renderList += `<li>${l_dayList[v_count]}</li>`;
                v_count ++;
            }
        }
        v_renderList += `</ul>`;
        return v_renderList;
    }

    f_setDetail(){
        /* Permet de définir ' v_detail' */
        switch (this.v_mode){
            case "Manuel": {
                if (this.v_state=="ON" && this.v_hFin){
                    this.v_detail = `
                    <ul>
                        <li>Heure d'arrêt : ${this.v_hFin}</li>
                    </ul>`;
                } else if (this.v_state=="ON" && this.v_dureeOff) {
                    this.v_detail = `
                        <ul>
                            <li>Durée avant arrêt : ${this.v_dureeOff} min</li>
                        </ul>`;
                }
                break;
            };
            case "Minuterie": {
                this.v_detail = `
                    <ul>
                        <li>Durée de fonctionnement : ${this.v_dureeOn} min</li>
                    </ul>`;
                break;
            };
            case "Cyclique": {
                if (this.v_hDebut){
                    this.v_detail = `
                        <ul>
                            <li>Durée 'ON' : ${this.v_dureeOn} min</li>
                            <li>Durée 'OFF' : ${this.v_dureeOff} min</li>
                            <li>Heure de début : ${this.v_hDebut}</li>
                        </ul>`;
                } else {
                    this.v_detail = `
                        <ul>
                            <li>Durée 'ON' : ${this.v_dureeOn} min</li>
                            <li>Durée 'OFF' : ${this.v_dureeOff} min</li>
                        </ul>`;
                }
                break;
            };
            case "Hebdomadaire": {
                    this.v_detail = `
                        <ul>
                            <li>Heure de début : ${this.v_hDebut}</li>
                            <li>Heure de fin : ${this.v_hFin}</li>
                            <li>Jours actifs : ${this.f_dayList()}</li>
                        </ul>`;
                break;
            };
        }
    }

    f_populateTable(){
        /* rempli le tableau de la page d'accueil avec les informations contenues dans le ficier JSON */
        let v_tbody = $(".home.tBody");
        let v_body = `
            <tr class="${this.v_tableColor}">
                <td>${this.v_nicName}<br>
                    (${this.v_emplacement})
                </td>
                <td>${this.v_state}${this.v_pauseOn}</td>
                <td>${this.v_mode}${this.v_modeCloned}</td>
                <td>${this.v_detail}</td>
            </tr>`;
        v_tbody.prepend(v_body);
    }

    f_refresh(jsonresponse, firstItem){
        /* Permet de définir / redéfinir les variables d'instance */
        this.f_resetData();
        this.f_setJsonOB(jsonresponse);
        this.f_setItem(firstItem);
        this.f_setSubItem();
        this.f_setRowColor(firstItem);
        this.f_ifCloned();
        this.f_ifPause();
        this.f_setDetail();
    }

}