const express = require('express');
const router = express.Router();

router.get('/todos', (req, res) => {

    res.send([
    {
        "id": 0,
        "name": "Sport",
        "done": false
    },
    {
        "id": 1,
        "name": "Blumen für Mama kaufen",
        "done": false
    }
    ]);
});

router.post('/todos', (req ,res) => {
    res.send(
        {
        "id": 1,
        "name": "Blumen für Mama kaufen",
        "done": false
        }
    );
});

router.get('/todos/{id}', (req, res) => {

});

router.delete('/todos/{id}', (req, res) => {

});

router.delete('/todos?done=true', (req, res) => {

});

router.patch('/todos/{id}', (req, res) => {

});








