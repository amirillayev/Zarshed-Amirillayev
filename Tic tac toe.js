count = 0;
   
  // document.getElementById("result").innerHTML= "result";
}
}

function reset (){
  //reset buttons to empty
 
  document.getElementById("cell_1").innerHTML = "";
  document.getElementById("cell_2").innerHTML = "";
  document.getElementById("cell_3").innerHTML = "";
  document.getElementById("cell_4").innerHTML = "";
  document.getElementById("cell_5").innerHTML = ""; 
  document.getElementById("cell_6").innerHTML = "";
  document.getElementById("cell_7").innerHTML = "";
  document.getElementById("cell_8").innerHTML = "";
  document.getElementById("cell_9").innerHTML = ""; 
  count=0;
};


function switchxo(){
  reset();
  var check= document.getElementById("myCheckBox").checked;
  
   if(!checkcheck){ 
     player = 1;

   } else {
     player = 0; 
   }
checkcheck = !checkcheck;
};

function button(){
  var b= document.getElementById("butt_reset");
  b.classList.toggle("active", 200);
}
