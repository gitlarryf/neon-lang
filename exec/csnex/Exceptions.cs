﻿using System;

namespace csnex
{
    [Serializable()]
    public class NeonException: ApplicationException
    {
        public string name;
        public Cell info;

        public NeonException() {
        }

        public NeonException(string message) : base(message)
        {
            name = message;
            info = new Cell(new ObjectString(""));
        }

        public NeonException(string message, params object[] args) : base(string.Format(message, args))
        {
            name = message;
            info = ((Cell)args[0]);
        }

        public NeonException(string message, System.Exception innerException) : base(message, innerException) {
        }
    }

    [Serializable]
    public class InvalidOpcodeException: NeonException
    {
        public InvalidOpcodeException() {
        }

        public InvalidOpcodeException(string message) : base(message) {
        }
    }

    [Serializable]
    public class BytecodeException: NeonException 
    {
        public BytecodeException() {
        }

        public BytecodeException(string message) : base(message) {
        }
    }

    [Serializable]
    public class NeonDivideByZeroException : NeonException
    {
        public NeonDivideByZeroException() {
        }

        public NeonDivideByZeroException(string message) : base(message) {
        }

        public NeonDivideByZeroException(string message, params object[] args) : base(string.Format(message, args)) {
        }

        public NeonDivideByZeroException(string message, Exception innerException) : base(message, innerException) {
        }
    }

    [Serializable]
    public class NeonStackOverflowException : NeonException
    {
        public NeonStackOverflowException() {
        }

        public NeonStackOverflowException(string message) : base(message) {
        }

        public NeonStackOverflowException(string message, params object[] args) : base(string.Format(message, args)) {
        }

        public NeonStackOverflowException(string message, Exception innerException) : base(message, innerException) {
        }
    }

    [Serializable]
    public class NotImplementedException: NeonException
    {
        public NotImplementedException() {
        }

        public NotImplementedException(string message) : base(message) {
        }
    }
}
