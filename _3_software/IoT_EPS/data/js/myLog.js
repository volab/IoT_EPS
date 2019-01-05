class C_MyLog{
    /* Permet d'afficher des éléments dans la console */
    constructor(){

    }

    f_formLog(v_target){
        /* Permet d'intercepter les données d'un formulaire et le affiche dans la console */
        var it = new FormData(v_target).entries();
        var current = {};
        console.log("\n", new Date().toLocaleString(), "\n");
        while ( ! current.done ) {
            current = it.next();
            let v_tmp = "";
            if (! current.done){
                for (let i=0; i<current.value.length; i++){
                    v_tmp += current.value[i] + " - "
                }
                console.info(v_tmp);
            }
        }
    }
}
