
export function listTasks(iterable) {
  let container = document.getElementById('data');
  let uList = document.createElement('ul');
  container.innerHTML = '';
  for (const item of iterable) {
  	let ulItem = document.createElement('li');
  	ulItem.appendChild(
  	  document.createTextNode(
  	  	`Title: ${item.title}; Completed: ${item.completed ? 'Yes' : 'No'}`
  	  )
  	);
  	uList.appendChild(ulItem);
  }
  container.appendChild(uList);
  return;
  

}

function getNewId(container) {
	// inefficient id generator, just to keep id seq properly going
	const sorted = container.sort((task1, task2) => task1.id - task2.id);
	return sorted[sorted.length - 1]['id'] + 1;

}

export function addTask(title, container) {
  let newTask = {
    title: title, 
    due_date: Math.floor(Date.now() + 3600 * 2 / 1000),
    starred: false,
    completed: false,
    id: getNewId(container)
  };
  container.push(newTask)
  console.log(`Task created with id: ${newTask.id} and title: ${newTask.title}`);
}