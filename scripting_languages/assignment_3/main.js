/*
    1. demonstate AJAX requests (GET, POST, DELETE, PATCH) content-type text and json
    2. results should be rendered with dome
    3. params of requests and response(demonstrate in dev console)


    Bonus:
    4. make wrapper above XMLHTTPrequest: methods GET,POST, content-type=json

*/
const URL = "https://6030301fa1e9d20017af1932.mockapi.io/api/v1/orders";


class Ajax {
    
    /**
    * Generic method for making requests
    * @param method, str, representing http verb, values get|post|patch|head|options|put
    * @param url, str, full url to resource
    * @param handler, function, callback for handling success reponse
    * @param data, object, data to send, default: null
    * @param contentType, str, value for content-type header, default: application/json
    * @returns 
    */
    #makeRequest(method, url, handler, data=null, contentType='application/json') {
        let xhr = new XMLHttpRequest();
        xhr.open(method, url, true);
        xhr.onload = () => {
            if ([200, 201, 204].includes(xhr.status)) {        
                handler(xhr.response, this);
            }
        }
        xhr.onerror = function (e) {
            console.log(`${e.type}: ${e.loaded} bytes transferred\n`);
        }

        // guard to eliminate user error
        data = (['get', 'head', 'options', 'delete'].includes(method) && data) ? null : data;
        data = ['post', 'patch', 'put'].includes(method) ? JSON.stringify(data) : data
        xhr.setRequestHeader("Content-Type", contentType);
        xhr.send(data);
    }

    get(url, handler=genericHandler) {
        this.#makeRequest('get', url, handler);
    }

    post(url, data, handler=genericHandler) {
        this.#makeRequest('post', url, handler, data);
    }

    patch(url, id, data, handler=genericHandler) {
        this.#makeRequest('patch', `${url}/${id}`, handler, data);
    }

    delete(url, id, handler=genericHandler) {
        this.#makeRequest('delete', `${url}/${id}`, handler);

    }
}

const ajax = new Ajax();

// ----- DOM handlers -----

function genericHandler(response) {
    console.log(response);
}

function handleGet(response, xhr) {
    JSON.parse(response).forEach(createListRecord);
}

function refreshList(response, xhr) {
    // do refresh of the list
    let listOut = document.getElementById('list-out');
    while(listOut.firstChild) { 
        listOut.removeChild(listOut.firstChild);
    }
    xhr.get(URL, handleGet);
}

/*
responseData = {
*   'id': <int>,
*   'title': <string>,
*   'amount': <int>,
* }
*/
function createListRecord(respData) {
    let listOut = document.getElementById('list-out');
    let item = document.createElement('li');
    let itemDiv = document.createElement('div');
    let deleteButton = document.createElement('button');
    deleteButton.appendChild(document.createTextNode('Delete'));
    deleteButton.setAttribute('id', `${respData['id']}_delete`);
    deleteButton.onclick = handleDelete
    let span = document.createElement('span');
    let liText = document.createTextNode(
        `Title: ${respData['title']} Amount: ${respData['amount']}`
    );
    
    // constructing DOM
    span.appendChild(liText);
    itemDiv.appendChild(span);
    itemDiv.appendChild(deleteButton);
    item.appendChild(itemDiv);
    listOut.appendChild(item);

}

//  ----- Event handler -----
function handleDelete(event) {
    let _id, rest;
    [_id, ...rest] = this.id.split('_');

    ajax.delete(URL, _id, refreshList)
}

function handleSubmit(event) {
    event.preventDefault();
    let inputs = document.getElementById("form").elements;
    
    ajax.post(
        URL, {amount: inputs["amount"].value, title: inputs['title'].value}, 
        refreshList);
    inputs["amount"].value = 0;
    inputs["title"].value = '';

}

/*
 * Reference: https://developer.mozilla.org/en-US/docs/Web/API/HTMLFormElement/submit_event
 */

function setupListeners() {
    let form = document.getElementById('form');

    // Bind the FormData object and the form element

    form.addEventListener('submit', handleSubmit);



}


document.addEventListener("DOMContentLoaded", (event) => ajax.get(URL, handleGet));
document.addEventListener("DOMContentLoaded", setupListeners);













