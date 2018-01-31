const usb = require("usb");

module.exports = {

	open() {
		let device = usb.findByIds(0x0483, 0xFEE0);

		device.open();

		let interface = device.interface(0);
		interface.claim();

		let inEndpoint = interface.endpoint(129);
		let outEndpoint = interface.endpoint(1);

		async function read(len) {
			return new Promise((resolve, reject) => {
				inEndpoint.transfer(1, (error, data) => {
					if (error) {
						reject(error);
					} else {
						resolve(data);
					}
				});
			});
		}

		async function write(data) {
			return new Promise((resolve, reject) => {
				outEndpoint.transfer(data, error => {
					if (error) {
						reject(error);
					} else {
						resolve();
					}
				});
			});
		}


		return {

			async getState(state) {
				await write(Buffer.from([0]));
				return await read(1);
			},

			async setState(state) {
				await write(Buffer.from([1, state]));
			}

		};

	}

};