# **Danke Delegate and Event Manager**

Simple and fast delegates for use in C++.

## **Create**
Create a delegate of a particular type
Delegate<T_RETURN_TYPE(T_ARGS...)>

## **Add**
Bind multiple objects/methods, static and const functions in a single delegate and send it to be executed.
Delegate.Add<T_RETURN_TYPE(T_ARGS...)>

## **Remove**
Remove functions from the delegate.
Delegate.Remove<T_RETURN_TYPE(T_ARG...)>

## **Invoke**
Call all functions in the delegate
Delegate(T_ARG...)

## **Use as an event using the EventManager**
Initialize the EventManager
EventManager.Initialize();
EventManager.subscribe<RETURN_TYPE(ARG_TYPE)>("EventName1", delegate1);
EventManager.subscribe<RETURN_TYPE(ARG_TYPE)>("EventName2", delegate2);

EventManager.Invoke<RETURN_TYPE(ARG_TYPE)>("EventName1", ARG_VALUE);
EventManager.Invoke<RETURN_TYPE(ARG_TYPE)>("EventName2", ARG_VALUE);

EventManager.unsubscribe<RETURN_TYPE(ARG_TYPE)>("EventName1", delegate1);
EventManager.unsubscribe<RETURN_TYPE(ARG_TYPE)>("EventName2", delegate2);
EventManager.destroy();

