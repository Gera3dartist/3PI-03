'use strict';

import {printer} from './modules/do_printing.js';
import {listTasks, addTask} from './modules/crud_for_data.js';
import {todoTasksData} from './modules/data.js';

const button = document.querySelector('input');
button.addEventListener('click', add_task);
listTasks(todoTasksData);


function add_task() {
  let title = prompt('Provide a task title: ');
  addTask(title, todoTasksData);
  listTasks(todoTasksData);
}
