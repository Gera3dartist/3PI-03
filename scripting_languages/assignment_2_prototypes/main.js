/*

------ Part2 - Prototypes,ineritance --------
1. create class hierarchy in prototype style
2. demonstrate polimorphizm (method overriding)
3. demonstrate class hierarchy in ES6
4. show hierarchi in function style (show private/public methods and fields)

*/

const User = function(name, age) {  // <--- constructor functions 
	this.name = name;
	this.age = age
};

User.prototype.showName = function() {console.log(this.name);}
User.prototype.incrementAge = function() {this.age += 1;}
User.prototype.showAge = function() {console.log(this.age);}

// ------------- 1. create class hierarchy in prototype style -------------

const Employee = function(name, age, department, salary) {
	// 2. demonstrate polimorphizm (method overriding) in this case overriding constructor
	User.call(this, name, age);
	this.department = department;
	this.salary = salary;
}

// 'inherit' prototype of User
Employee.prototype = Object.create(User.prototype);

// ------- Public API
// this - is reference to instance of the class (self)
Employee.prototype.showSalary = function() {console.log(this.salary);}
Employee.prototype.changeSalaryOn = function(diff) {this.salary = this.salary + diff;}

// 2. demonstrate polimorphizm - showName is now constructed as call 
// to parent method  and new logic for Employee
Employee.prototype.showName = function() {
	User.prototype.showName.call(this);
	console.log(`Department: ${this.department}`);
}

console.log(`-------------- Prototype inheritance ---------------`);

let stepan = new Employee('Stepan', 32, 'MarsResercher', 3450);

// User's (parent's) methods
stepan.showName();
stepan.showAge();

// Employee methods
stepan.showSalary();
stepan.changeSalaryOn(-100);
stepan.showSalary();


// -------------    3. demonstrate class hierarchy in ES6 -------------

class BaseComponent {
    constructor(name, message) {
        this._name = name;
        this.message = message;
    }

    get name () {return this._name;}
    set name (name) {this._name = name;}
    doSomething() {
    	console.log(`Component: ${this._name} says: ${this.message}`);
    }
}

class ConcreteComponent extends BaseComponent {
	#concreateArg = '';

	constructor(concreteArg, ...args) {
		super(...args);
		this.#concreateArg = concreteArg;
	}

	doSomething() {
		BaseComponent.prototype.doSomething.apply(this);
		console.log(`ConcreteComponent.doSomething - ${this.#concreateArg}`)

	}

}

console.log(`-------------- ES6 Classes ---------------`);
let comp = new ConcreteComponent('MyConcreteArg', 'someName', 'someMessage');
comp.doSomething();


// ------------- 4. show hierarchi in function style (show private/public methods and fields) -------------

const BaseMamal = function (type, amountOflegs=4) {

	this.type = type;

	// private field
	let _DNA = 'TTTTCCCCAAAAGGGGTTTTCCCCAAAAGGGGTTTTCCCCAAAAGGGGTTTTCCCCAAAAGGGG';


	// binding this to self, to be able use it in private functions
	const self = this

	// private function
	// implemenation of walking
	function _walkImplementattion () {
		Array(amountOflegs)
			.fill('do step')
			.forEach(
				(action, index, _) => console.log(`leg - ${index}: ${action}`)
			);

	}
	this.showDNA = function () {return _DNA};
	this.showType = function() {
		console.log(`type is: ${self.type}`);
	}

	this.walk = function () {
		console.log(`Animal of type ${self.type} is walking:`);
		return _walkImplementattion();
	}
	
}

const Human = function (name, amountOflegs=2) {
	this.name = name;
	BaseMamal.call(this, 'human', amountOflegs);

	self = this;
	this.showDNA = function () {
		return `${new BaseMamal().showDNA()} + HumanDNA`};

	this.showName = function() {
		console.log(`name is : ${self.name}`)};

}

console.log(`-------------- Function inheritance ---------------`);
const baseMamal = new BaseMamal('livingThing');
baseMamal.walk();

const newHuman = new Human('Arsen');
newHuman.showName();
console.log(newHuman.showDNA());
newHuman.walk();



