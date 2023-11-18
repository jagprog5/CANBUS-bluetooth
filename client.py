# import asyncio
# from bleak import BleakScanner

# async def main():
#     devices = await BleakScanner.discover()
#     for d in devices:
#         print(d)

# asyncio.run(main())

import asyncio
from bleak import BleakClient

async def connect_and_write():
    # Replace with the address of your BLE peripheral
    device_address = "81:F4:66:B7:FC:88"

    async with BleakClient(device_address) as client:
        print(f"Connected: {client.is_connected}")

        # Replace with the UUID of the characteristic you want to write
        characteristic_uuid = "02401BCD-38A9-4218-AB87-128397ED1C3B"

        # Replace with the data you want to write to the characteristic
        data_to_write = b"yes"

        # Write data to the characteristic
        await client.write_gatt_char(characteristic_uuid, data_to_write)

        print(f"Data written to characteristic {characteristic_uuid}")

# Run the event loop to execute the asynchronous code
asyncio.run(connect_and_write())
