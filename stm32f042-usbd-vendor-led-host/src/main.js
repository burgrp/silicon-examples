const driver = require("./driver.js");


async function start() {
	
	let device = await driver.open();
	
	if (process.argv[2] === "get") {
		console.info((await device.getState()).readUInt8(0));
	} else if (process.argv[2] === "set") {
		await device.setState(parseInt(process.argv[3]));
	} else {
		console.error("use:");
		console.error("\tusbled get");
		console.error("\tusbled set <0|1>");
	}
	
}

start().catch(console.error);