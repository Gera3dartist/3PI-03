'use strict';

// class representing base clas for all autos
const BaseVehicle = function(brand, mileage, type, basePrice) {
	this.brand = brand;
	this.mileage = mileage;
	this.type = type;
	this.basePrice = basePrice;
}


BaseVehicle.prototype.calculatePrice = function() {
	return this.basePrice * (this.mileage > 100000 ? 0.7 : 0.8);
}

BaseVehicle.prototype.showInfo = function() {
	return `Brand: ${this.brand}, mileage: ${this.mileage}, price: ${this.calculatePrice()}`;
}

const BaseBus = function (brand, mileage, type, basePrice, numberOfseats) {
	BaseVehicle.call(this);
	this.numberOfseats = numberOfseats;
}

BaseBus.prototype = Object.create(BaseVehicle.prototype)


