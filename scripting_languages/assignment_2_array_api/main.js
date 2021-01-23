'use strict';
/*
Methods: 
1. forEach, 
2. modify element with foreach, 
3. filter, 
4. map, 
5. every,
6. some, 
7. reduce, 
8. reduceRight

What should be done:
	2 examples for each API method
ES6 desirable
*/

const API_URL = 'https://5d4908fd2d59e50014f20f15.mockapi.io/api/v1/orders';
const OUT_LIST_ID = 'outList';

const storeHandler = function() {
	let datastore = [];
	return {
		set: (data) => {datastore = data;},
		get: () => datastore,
	};

}

const STORE = storeHandler();


function fetchData(onResponse, url=API_URL) {
	fetch(url).then(response => response.json()).then(data => {
		STORE.set(data);
		onResponse(STORE.get())
	});
}


const makeRenderer = (fieldsToIgnore=['createdAt']) => {
	let _fieldsToIgnore = new Set(fieldsToIgnore)

	const dropChildren = (parent) => {
		while(parent.firstChild) { 
			parent.removeChild(parent.firstChild);
		}
	}
	const createListNode = (data) => {
			let li = document.createElement('li');
			li.setAttribute('id', `order_${data.id}`);

			// 1. forEach
			// 3. filter
			// 4. map

			(Object.entries(data)
				.filter(([key, value]) => !_fieldsToIgnore.has(key))
				.map(([key, value]) => {
					let span = document.createElement('span');
					span.appendChild(document.createTextNode(`${key}: ${value}; `))
					return span})
				.forEach((spanItem) => li.appendChild(spanItem)));
			return li;	
	};

	return {
		renderResponse: (data) => {
			const outputDiv = document.getElementById('out');
			const _outList = document.getElementById(OUT_LIST_ID);
			const outList = _outList === null ? document.createElement('ul') : _outList;
			outList.setAttribute('id', OUT_LIST_ID); 
			dropChildren(outList);
			// create list 
			let listNodes = data.map(createListNode);

			// append list nodes to output list
			listNodes.forEach((element) => outList.appendChild(element));

			outputDiv.appendChild(outList);
		}
	}
}
	
const renderer = makeRenderer();



// 2. modify element with foreach, 
function modifyData(data){
	data.forEach((value, index, arr) => arr[index].amount = 0);
	return data;
}

// 5. every,
// 6. some, 
function someEverryDemo(data) {
	let lteIndex = 50;
	let gtIndex = 150;
	console.log(`all transaction are positive: ${data.every(item => item.amount >= 0)}`);
	console.log(`all equals 0: ${data.every(item => item.amount === 0)}`);
	console.log(`some of transaction are smaller than ${lteIndex}: ${data.some(item => item.amount < lteIndex)}`);
	console.log(`some of transaction are greater than ${gtIndex}: ${data.some(item => item.amount > gtIndex)}`);

}


// 7. reduce, 
function findMax(data) {
	return [data.reduce((a, b) => a.amount > b.amount ? a : b)]
}

// 8. reduceRight
const compose = (...args) => (value) => args.reduceRight((acc, fn) => fn(acc), value)

function pipelineDemo(data) {
	console.log(`initial result: ${data.amount}`);
	
	let result = compose(
		(amount) => amount - amount * 0.05, // 5% taxes
		(amount) => amount + 20, //bank fee
	)(data.amount);

	console.log(`reduced result: ${result}`);
}


// ------------ Generic part ------------

function genericHandler(data, processor=(data) => data) {
	let _data = processor(data);
	return renderer.renderResponse(_data);
}


function setupListeners() {
	const fetchButton = document.getElementById("fetchData");
	const maxButton = document.getElementById("showMax");
	const modifyButton = document.getElementById("modifyItems");
	const someEveryDemoButton = document.getElementById("someEveryDemo");
	const pipelineDemoButton = document.getElementById("pipelineDemo");
	maxButton.disabled = true;
	modifyButton.disabled = true;
	someEveryDemoButton.disabled = true;
	pipelineDemoButton.disabled = true;

	fetchButton.addEventListener('click', event => fetchData(genericHandler));
	fetchButton.addEventListener(
		'click', (event) => {
			console.log('enabling buttons');
			const maxButton = document.getElementById("showMax");
			const modifyButton = document.getElementById("modifyItems");
			const someEveryDemoButton = document.getElementById("someEveryDemo");
			const pipelineDemoButton = document.getElementById("pipelineDemo");
			maxButton.disabled = false;
			modifyButton.disabled = false;
			someEveryDemoButton.disabled = false;
			pipelineDemoButton.disabled = false;

		});


	maxButton.addEventListener('click', event => fetchData((data) => genericHandler(data, findMax)));
	modifyButton.addEventListener('click', event => fetchData((data) => genericHandler(data, modifyData)));
	someEveryDemoButton.addEventListener('click', event => someEverryDemo(STORE.get()));
	pipelineDemoButton.addEventListener('click', event => pipelineDemo(STORE.get()[0]));

};


document.addEventListener("DOMContentLoaded", setupListeners);















