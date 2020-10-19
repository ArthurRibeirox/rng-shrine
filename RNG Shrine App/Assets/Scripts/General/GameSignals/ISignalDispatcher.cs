namespace GameSignals
{
    public interface ISignalDispatcher
    {
        void AddListener<T>(SignalDispatcher.SignalDelegate<T> listener) where T : Signal;
        void RemoveListener<T>(SignalDispatcher.SignalDelegate<T> listener) where T : Signal;
        void Dispatch(Signal signal);
        void Dispatch<T>() where T : Signal;
        bool HasListeners<T>();
        void Clear();
    }
}