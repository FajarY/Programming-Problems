using System.Collections;
using System.Collections.Generic;
using System;
using System.Threading;

public class ThreadRunner
    {
        private Thread _thread;
        private Semaphore _mainSemaphore;
        private bool _isAlive;
        private bool _isRunning;
        private Action _executingMethod;
        private Semaphore _waitSemaphore;

        private object _runningLock;
        private object _waitingLock;
        private object _aliveLock;

        private bool _requestingWait;

        public bool isRunning { get => _isRunning; }
        public bool isAlive { get => _isAlive; }
        private bool _isStopping;

        public ThreadRunner()
        {
            _runningLock = new object();
            _waitingLock = new object();
            _aliveLock = new object();

            _isAlive = true;
            _isRunning = false;
            _mainSemaphore = new Semaphore(0, 1);
            _thread = new Thread(Execute);
            _thread.IsBackground = true;
            _thread.Start();
        }
        public void Run(Action method)
        {
            lock (_aliveLock)
            {
                if (!_isAlive)
                {
                    throw new Exception("Thread is currently not alive, cannot run method!");
                }
            }
            lock (_runningLock)
            {
                if (_isRunning)
                {
                    throw new Exception("Thread is currently running, cannot run again!");
                }
                _isRunning = true;
                _executingMethod = method;
                _mainSemaphore.Release();
            }
        }
        private void Execute()
        {
            _waitSemaphore = new Semaphore(0, 1);
            while (_isAlive)
            {
                try
                {
                    _mainSemaphore.WaitOne();
                    if (_executingMethod != null)
                    _executingMethod();
                }
                catch (ThreadAbortException)
                {
                    Thread.ResetAbort();

                    if(_isStopping)
                    ThreadStop();
                }
                catch (Exception ex)
                {
                    ThreadStop();
                    throw new Exception($"ThreadRunner stopped, ex {ex}");
                }
                finally
                {
                    lock (_runningLock)
                    {
                        _isRunning = false;
                        _executingMethod = null;
                        lock (_waitingLock)
                        {
                            if (_requestingWait)
                            {
                                _requestingWait = false;
                                _waitSemaphore.Release();
                            }
                        }
                    }
                }
            }
        }
        private void ThreadStop()
        {
            lock (_aliveLock)
            {
                _isAlive = false;
            }
        }
        public bool Cancel()
        {
            bool isCancelling = false;
            lock (_runningLock)
            {
                if (_isRunning)
                {
                    _thread.Abort();
                    isCancelling = true;
                }
            }
            if (isCancelling)
            {
                Wait();
                return true;
            }
            return false;
        }
        public void Stop()
        {
            if (_thread.IsAlive)
            {
                _isStopping = true;
                _thread.Abort();
                _thread.Join();
            }
        }
        public void Wait()
        {
            lock (_runningLock)
            {
                lock (_waitingLock)
                {
                    if (!_isRunning) return;

                    if (_requestingWait)
                    {
                        throw new Exception("Cannot wait thread, Only one thread can wait!");
                    }
                    _requestingWait = true;
                }
            }
            _waitSemaphore.WaitOne();
        }
    }
