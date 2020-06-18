## Smart Cart system -Team MILTON

Initialized the Arduino controller for RFID and bluetooth, which will help communicate with the different cart components.
Second part is Tag detection and barcode scanner, which will help scan the barcode from the iden as soon as it was dropped into the cart.
Different sensors at different location in the store will help in the navigation of the trolley, by calculating the relative position of the cart in the store.

For calculating the minimum route to the destination item, **Travelling salesman algorithm and Dijkestra's Single Source Shortest path Algorithm** can be used.

We can add further more features like displaying a Item list, retrived from the user's database in cloud, which will help them check the abailability of the item in the store while at home(with the help of Application, linked to the database server, if required).
