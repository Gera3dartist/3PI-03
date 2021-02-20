------------- Lection 1 -------------

- Selectors in browser console:
 1. $0 - get currently selected element
 2. $('<html_tag>') - select single element matching tag
 3. $$('<html_tag>') - select all elements matching tag

- API for searching elements in DOM:
 1. by node attributes:
 	- document.getElementById(<id>)
 	- document.getElementByTagName(<tag_name>)
 	- document.getElementByClassName(<class_name>)
 2. by query:
 	- document.querySelectorAll('<tagName1> <tagName2>')
 	- document.querySelector('<tagName1> <tagName2>')
 3. traversing DOM tree:
 	<node>.nextSibling()

- API of node in DOM:
 1. properties
 	<node>.innerHtml  - text of the node
 	<node>.style  - object of type CSSStyleDeclaration with attributes/values 
 		for styling at given moment for given element
 	<node>.classList - collection of css classes wrapped with DOMTokenList, for given element
 
 
------------- Lection 2 -------------
Element Creation
	var h = document.createElement("H3");
	h.innerHTML = 'Hello';
	document.body.appendChild(h);

// Creation event listener:
h.onclick = () => {console.log('foo bar');}
// OR
h.addEventListener('click', (event) => console.log(`${event.target}`), ...funcN);

// OR
<p onclick = "this.style.color = 'red'">
// Removing event listener:
h.onclick = null;
// OR
h.removeEventListener(funcName)  - wont work for function expression


------------- Lection 3, 4 -------------

	XMLHttpRequest
	General approach for working with XMLHttpRequest
	1. create object
	var xhr = new XMLHttpRequest();
	2. open - setup message
	3. onload(..) setting up callbacks when server will respond
	4. send(..) data to send
