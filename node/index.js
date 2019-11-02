const crypto = require('crypto');
const util = require('util');

const sleep = util.promisify(setTimeout);

function random_bit() {
    return crypto.randomBytes(1).readUInt8(0) & 1;
}

class A {
    constructor(a) {
        this.a;
    }

    async slow_assignment(value) {
        if (random_bit() == 0) {
            await sleep(1000);
        }

        this.a = value;
    }
}

async function main() {
    let a = new A(0);

    await Promise.all([
        a.slow_assignment(1),
        a.slow_assignment(2),
    ]);

    console.log(a.a);
}

(async () => {await main()})();
