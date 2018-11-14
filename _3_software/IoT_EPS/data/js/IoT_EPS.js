function loadJSON(callback) { 
    var xobj = new XMLHttpRequest();
    xobj.overrideMimeType("application/json");
    xobj.open('GET', 'config2.json', true);
    xobj.onreadystatechange = function () {
       if (xobj.readyState == 4 && xobj.status == "200") {
          callback(xobj.responseText);
       }
    }
    xobj.send(null);
}
    
loadJSON(function(response) {
      jsonresponse = JSON.parse(response);
      //alert(jsonresponse["general"]["hostName"]);
      /* TODO: parcourir le fichier config2.json et l'aficher dans chaque
       * prise correspondante
       */
});
