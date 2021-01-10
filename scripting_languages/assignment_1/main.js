'use strict';
/*
What should be done:

1. function declaration,
2. function parameters, default parameters
3. function expression 

4. passing anonymous func as param,
5. assign func to var
6. arrow function

---closures
7. show different variant of closures
8. pattern module
9. show closures and pattern module for real html elements(e.g. closure with anonymous function)

*/

const MAX_COPIES = 3;


// 5. assign func to var
const fancyLogger = function(message) {
	let timestamp = '[' + new Date().toISOString() + '] ';
    console.log(timestamp, message);
}

// same rowHandler function, but shaped in declarative(more readable, IMO, way)
function handleLineCount(outputList, size){
	let times;
	if (size > outputList.childElementCount) {
		times = size - outputList.childElementCount;
		cloneRow(times, outputList);
	} else {
		times = outputList.childElementCount - size;
		removeRow(times, outputList);
	}
}

function removeRow(times, outputList){
	if (times <= 0) {return;}
	outputList.removeChild(outputList.lastChild);
	return removeRow(times-1, outputList);
}

function cloneRow(times, outputList) {
	if (times <= 0) return;
	outputList.appendChild(outputList.children[0].cloneNode(true));
	return cloneRow(times-1, outputList);
}


// 7. show different variant of closures
function makeFontSizer(size) {
  return function() {
    document.body.style.fontSize = size + 'px';
  };
}


var size14 = makeFontSizer(14);
var size16 = makeFontSizer(16);



// 8. pattern module
const makeCounter = function() {
	/*
	idea is simple, 
		everything public - goes in return statement
		everyting private, defined before return
	*/
	let _direction = 1;
	let _counter = 0;

	return {
		changeDirection: () => {_direction = _direction * -1;},
		getValue: () => {return _counter},
		run: () => {_direction > 0 ? _counter += 1 : _counter -= 1;}
	};
}
let counter = makeCounter();


// 1. function declaration,
function setupListeners() {
	const _input = document.getElementById("data-input");
	const copyController = document.getElementById("amount");
	const listRowController = document.getElementById("row-amount");
	const counterController = document.getElementById("counter-toggle");

	const outputList = document.getElementById("list-output");


	// 2. function parameters, default parameters
	// 3. function expression 
	const makeCopies = function (source, _times=0, separator=',') {
		let times = _times > MAX_COPIES ? MAX_COPIES : _times;
		source = source.split(separator)[0];
		let result = times > 0 ? Array(times).fill(source).join(separator) : source;
		fancyLogger(result);
		return result;
	}

	// add event handler to make text copying
	// 4. passing anonymous func as param,
	copyController.onchange = function (event) { 
		fancyLogger("catched copyController onchange, times: "+parseInt(event.target.value));
		for (let i = 0; i < outputList.children.length; i++){
			let __input = outputList.children[i].getElementsByTagName("input")[0]
			__input.value = makeCopies(__input.value, parseInt(event.target.value));
		}
	};

	// 6. arrow function
	// add event handler to reflect changes in result section
	_input.onchange = (event) => {
		for (let i = 0; i < outputList.children.length; i++){
			let __input = outputList.children[i].getElementsByTagName("input")[0]
			__input.value = event.target.value;
		}
	};
	// 7. show different variant of closures
	// example of closure: where outputList is taken from env of setupListeners
	listRowController.onchange = (event) => {
		let size = parseInt(event.target.value);
		size = Number.isNaN(size) ? 1 : size;
		size = size > MAX_COPIES ? MAX_COPIES : size;
		handleLineCount(outputList, size);
	};

	counterController.addEventListener('click', (event) => {
		fancyLogger('Catched click on counter toggle');
		counter.changeDirection();
	});

	// --- setup onclick handlers
	document.getElementById('size-16').onclick = size16;
	document.getElementById('size-14').onclick = size14;
}

setupListeners();

// example of IIFE
(function() {
	const counterElement = document.getElementById("counter");
	setInterval(() => {
		counterElement.value = counter.getValue();
		counter.run();
	}, 1000);
})();



function processCallback(message, func) {
	let result = func(message);
	return result;
}

processCallback('something', fancyLogger);



















