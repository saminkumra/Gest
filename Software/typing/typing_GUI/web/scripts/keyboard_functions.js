var sentence = document.getElementById('sentence');


var words = [];
var potential_depth = 10;
var xmlhttp;
if (window.XMLHttpRequest) { // code for IE7+, Firefox, Chrome, Opera, Safari
    xmlhttp = new XMLHttpRequest();
} else { // code for IE6, IEpotential_depth
    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
}
xmlhttp.onreadystatechange = function() {
    if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
        var text = xmlhttp.responseText;
        // Now convert it into array using regex
        words = text.split(/\r?\n/);
		//console.log(words);
    }
}
xmlhttp.open("GET", "../20k.txt", true);
xmlhttp.send();
console.log(words);
function update_words(keys, words) {
	//console.log(keys);
	if(keys.length == 0) {
		return [];
	}
	var potential_words = [];
		for (var j = 0; j < words.length; j++) {
			var word_fits = true;
			if (j == words.length - 1) {
				break;
			}
			if(potential_words.length >= potential_depth) {
				break;
			}
			for (var i = 0; i < keys.length; i++) {
				try {
					if (!keyToChar.get(keys[i]).includes(words[j][i], 0)) {
						word_fits = false;
						break;
					}
				}
				catch(err){
					word_fits = false;
					break;
				}
			}
			if(word_fits) {
				potential_words.push(words[j]);
			}
            if(potential_words.length >= potential_depth) {
				break;
			}
		}
	console.log(potential_words);
	return potential_words;
}
const keyToChar = new Map([
	["KeyS", ["q", "a", "z"]],
	["KeyA", ["w", "s", "x"]],
	["KeyW", ["e", "d", "c"]],
	["KeyD", ["r", "f", "v", "t", "g", "b"]],
	["Digit9", ["y", "h", "n", "u", "j", "m"]],
	["Digit8", ["i", "k"]],
	["Digit7", ["o", "l", "p"]],
	["Digit6", []]
]);

var keys = [];
var current_index = 0;
var first_word = true;
document.addEventListener('keydown', (event) => {
	var name = event.key;
	var name_int = parseInt(name);
	var code = event.code;
	//console.log(keys);
	//console.log(name);
	console.log(code);
	//console.log(keyToChar.get(name_int))
	if((code.includes("Digit") && name_int >= 7) || code.includes("Key") ) {
		//keys.push(parseInt(name_int));
		keys.push(code);
		console.log(keys);
		var potential_words = update_words(keys, words);
		for(var i = 0; i < potential_depth; i++) {
			var table = document.getElementById('autocomplete_words');
			var row = table.getElementsByTagName("tr")[0];
			var th = row.getElementsByTagName("th")[i];
			if(potential_words[i] != undefined) {
				th.innerHTML = potential_words[i];
			}
			else {
				th.innerHTML = "";
			}
			if(i == current_index) {
				th.style.color = "yellow";
			}
			else {
				th.style.color = "black";
			}
			
		}
	}
	else if (code == "Digit0") {
		var potential_words = update_words(keys, words);
		var sentence = document.getElementById('sentence');
		if(potential_words.length > 0) {
			if(first_word) {
				potential_words[current_index] = potential_words[current_index].charAt(0).toUpperCase() + potential_words[current_index].slice(1);
				first_word = false;
			}
			sentence.innerHTML = sentence.innerHTML + " " + potential_words[current_index];
			for(var i = 0; i < potential_depth; i++) {
				var table = document.getElementById('autocomplete_words');
				var row = table.getElementsByTagName("tr")[0];
				var th = row.getElementsByTagName("th")[i];
				th.innerHTML = "";
			}
		}
		else {
			sentence.innerHTML = sentence.innerHTML + ". ";
			first_word = true
		}
		current_index = 0;
		keys = [];
	}
	else if (code == "Space") {
		var potential_words = update_words(keys, words);
		current_index = (current_index + 1) % potential_depth;
		for(var i = 0; i < potential_words.length; i++) {
			var table = document.getElementById('autocomplete_words');
			var row = table.getElementsByTagName("tr")[0];
			var th = row.getElementsByTagName("th")[i];
			if(i == current_index) {
				th.style.color = "yellow";
			}
			else {
				th.style.color = "black";
			}
		}
	}
	// else if (code == "Space") {
	// 		keys.pop();
	// 		var potential_words = update_words(keys, words);
	// 		for(var i = 0; i < potential_depth; i++) {
	// 			var table = document.getElementById('autocomplete_words');
	// 			var row = table.getElementsByTagName("tr")[0];
	// 			var th = row.getElementsByTagName("th")[i];
	// 			if(potential_words[i] != undefined) {
	// 				th.innerHTML = potential_words[i];
	// 			}
	// 			else {
	// 				th.innerHTML = "";
	// 			}
				
	// 			if(i == current_index) {
	// 				th.style.color = "yellow";
	// 			}
	// 			else {
	// 				th.style.color = "black";
	// 			}
				
	// 		}
	// 		var sentence = document.getElementById('sentence');
	// 		if(keys.length == 0) {
	// 			if(first_word) {
	// 				sentence.innerHTML = sentence.innerHTML.slice(0, -2);
	// 			}
	// 			else {
	// 				var sentence_text = sentence.innerHTML;
	// 				var sentence_words = sentence_text.split(" ");
	// 				var sub_length = sentence_text.length - sentence_words[sentence_words.length-1].length - 1;
	// 				sentence.innerHTML = sentence.innerHTML.substring(0, sub_length);
	// 			}
				
	// 		}
	// 		else if(!first_word && keys.length > 0) {
	// 			var sentence_text = sentence.innerHTML;
	// 			var sentence_words = sentence_text.split(" ");
	// 			var sub_length = sentence_text.length - sentence_words[sentence_words.length-1].length - 1;
	// 			sentence.innerHTML = sentence.innerHTML.substring(0, sub_length);
	// 			keys = [];
	// 		}
	// }

	// Alert the key name and key code on keydown
	//alert(`Key pressed ${name} \r\n Key code value: ${code}`);
  }, false);