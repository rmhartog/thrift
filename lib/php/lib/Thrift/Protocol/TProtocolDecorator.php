<?php
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 * @package thrift.protocol
 */

namespace Thrift\Protocol;

use Thrift\Protocol\TProtocol;

abstract class TProtocolDecorator extends TProtocol {

  /**
   * The concrete protocol
   *
   * @var TProtocol
   */
  private $protocol_;

  public function __construct($protocol) {
    parent::__construct($protocol->getTransport());
    $this->protocol_ = $protocol;
  }

  public function writeMessageBegin($name, $type, $seqid) {
    return $this->protocol_->writeMessageBegin($name, $type, $seqid);
  }

  public function writeMessageEnd() {
    return $this->protocol_->writeMessageEnd();
  }

  public function writeStructBegin($name) {
    return $this->protocol_->writeStructBegin($name);
  }

  public function writeStructEnd() {
    return $this->protocol_->writeStructEnd();
  }

  public function writeFieldBegin($fieldName, $fieldType, $fieldId) {
    return $this->protocol_->writeFieldBegin($fieldName, $fieldType, $fieldId);
  }

  public function writeFieldEnd() {
    return $this->protocol_->writeFieldEnd();
  }

  public function writeFieldStop() {
    return $this->protocol_->writeFieldStop();
  }

  public function writeMapBegin($keyType, $valType, $size) {
    return $this->protocol_->writeMapBegin($keyType, $valType, $size);
  }

  public function writeMapEnd() {
    return $this->protocol_->writeMapEnd();
  }

  public function writeListBegin($elemType, $size) {
    return $this->protocol_->writeListBegin($elemType, $size);
  }

  public function writeListEnd() {
    return $this->protocol_->writeListEnd();
  }

  public function writeSetBegin($elemType, $size) {
    return $this->protocol_->writeSetBegin($elemType, $size);
  }

  public function writeSetEnd() {
    return $this->protocol_->writeSetEnd();
  }

  public function writeBool($value) {
    return $this->protocol_->writeBool($value);
  }

  public function writeByte($value) {
    return $this->protocol_->writeByte($value);
  }

  public function writeI16($value) {
    return $this->protocol_->writeI16($value);
  }

  public function writeI32($value) {
    return $this->protocol_->writeI32($value);
  }

  public function writeI64($value) {
    return $this->protocol_->writeI64($value);
  }

  public function writeDouble($value) {
    return $this->protocol_->writeDouble($value);
  }

  public function writeString($value) {
    return $this->protocol_->writeString($value);
  }

  public function readMessageBegin(&$name, &$type, &$seqid) {
    return $this->protocol_->readMessageBegin($name, $type, $seqid);
  }

  public function readMessageEnd() {
    return $this->protocol_->readMessageEnd();
  }

  public function readStructBegin(&$name) {
    return $this->protocol_->readStructBegin($name);
  }

  public function readStructEnd() {
    return $this->protocol_->readStructEnd();
  }

  public function readFieldBegin(&$name, &$fieldType, &$fieldId) {
    return $this->protocol_->readFieldBegin($name, $fieldType, $fieldId);
  }

  public function readFieldEnd() {
    return $this->protocol_->readFieldEnd();
  }

  public function readMapBegin(&$keyType, &$valType, &$size) {
    return $this->protocol_->readMapBegin($keyType, $valType, $size);
  }

  public function readMapEnd() {
    return $this->protocol_->readMapEnd();
  }

  public function readListBegin(&$elemType, &$size) {
    return $this->protocol_->readListBegin($elemType, $size);
  }

  public function readListEnd() {
    return $this->protocol_->readListEnd();
  }

  public function readSetBegin(&$elemType, &$size) {
    return $this->protocol_->readSetBegin($elemType, $size);
  }

  public function readSetEnd() {
    return $this->protocol_->readSetEnd();
  }

  public function readBool(&$value) {
    return $this->protocol_->readBool($value);
  }

  public function readByte(&$value) {
    return $this->protocol_->readByte($value);
  }

  public function readI16(&$value) {
    return $this->protocol_->readI16($value);
  }

  public function readI32(&$value) {
    return $this->protocol_->readI32($value);
  }

  public function readI64(&$value) {
    return $this->protocol_->readI64($value);
  }

  public function readDouble(&$value) {
    return $this->protocol_->readDouble($value);
  }

  public function readString(&$value) {
    return $this->protocol_->readString($value);
  }
}
